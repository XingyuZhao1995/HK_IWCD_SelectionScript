#include "analysis/MDTEventCheck.h"

// -------- Public member functions --------

// ********************************************************
MDTEventCheck::MDTEventCheck(std::string in_list_name, std::string out_name) :
  BaseMDTAnalysis(in_list_name){
// ********************************************************

  fout_name = out_name;

}

// ********************************************************
MDTEventCheck::~MDTEventCheck(){
// ********************************************************

  delete fout;

}

// ********************************************************
void MDTEventCheck::OverallInitialization(){
// ********************************************************

  // Create output file
  fout = new TFile(fout_name.data(),"recreate");

  // Create output tree
  // (Attach it to the output file so full baskets are flushed to disk instead of kept in memory)
  tout.SetNameTitle("events","events");
  tout.SetDirectory(fout);

  // (Tree branches)
  tout.Branch("type",&type,"type/I");

  tout.Branch("hits_ID_posX",&hits_ID_posX);
  tout.Branch("hits_ID_posY",&hits_ID_posY);
  tout.Branch("hits_ID_posZ",&hits_ID_posZ);
  tout.Branch("hits_ID_charge",&hits_ID_charge);
  tout.Branch("hits_ID_intidx",&hits_ID_intidx);
  tout.Branch("hits_ID_PDG",&hits_ID_PDG);

  tout.Branch("hits_OD_posX",&hits_OD_posX);
  tout.Branch("hits_OD_posY",&hits_OD_posY);
  tout.Branch("hits_OD_posZ",&hits_OD_posZ);
  tout.Branch("hits_OD_charge",&hits_OD_charge);
  tout.Branch("hits_OD_intidx",&hits_OD_intidx);
  tout.Branch("hits_OD_PDG",&hits_OD_PDG);

}

// ********************************************************
void MDTEventCheck::RunEventAnalysis(AnaMDTEvent &event){
// ********************************************************

  // Look at two pile-up cases
  // Case 1: two interactions in the same bunch
  int bunch_idx_1 = FindTwoIntBunchIdx(event);
  if(bunch_idx_1 >= 0){
    FillOutputTree(event,1);
  }

  // Case 2: one ME + one interaction in the same bunch
  int bunch_idx_2 = FindOneMEOneIntBunchIdx(event);
  if(bunch_idx_2 >= 0){
    FillOutputTree(event,2);
  }

}

// ********************************************************
void MDTEventCheck::SaveOutputFile(){
// ********************************************************

  fout->cd();

  tout.Write();
  // Detach before closing, otherwise TFile::Close() would delete this member tree
  tout.SetDirectory(nullptr);

  fout->Close();

}

// -------- Private member functions --------

// ********************************************************
int MDTEventCheck::FindTwoIntBunchIdx(AnaMDTEvent &event){
// ********************************************************

  // -------- Basic selection --------

  // Collect bunch -> interaction mapping using true information
  std::map<int,std::vector<int>> map_bunch_int_idx;
  for(int i = 0; i < event.n_int; i++){
    map_bunch_int_idx[event.vec_nu_bunch_idx[i]].push_back(i);
  }

  // Find out if there is a bunch with exactly two interactions
  // In principle there exists cases where more than one bunch having
  // two interactions, but given the mean number of spill interactions,
  // this probability should be very small
  int bunch_index = -1;
  std::vector<int> vec_bunch_int_index;
  for(auto &element : map_bunch_int_idx){
    if(element.second.size() == 2){
      bunch_index = element.first;
      vec_bunch_int_index = element.second;
      break;
    }
  }

  // Not found
  if(bunch_index < 0) return -1;

  // -------- Interaction requirement --------

  // Not just select random two interactions, require some additional
  // cuts on the interactions to have "good" event qualities
  // At least one interaction should pass the cuts

  // Loop over true interactions
  bool has_good_int = false;
  for(int index : vec_bunch_int_index){
    if(TrueInteractionCut(event,index)) has_good_int = true;
  }
  if(!has_good_int) return -1;

  // -------- PMT hits requirement --------

  // Collect all PMT hits belong to this bunch
  MiscUtils::CollectBunchPMTHits(event,bunch_index,vec_PMT_hit_ID,vec_PMT_hit_OD);

  // ID hit number should be large enough
  if(vec_PMT_hit_ID.size() < 80) return -1;

  // Now the bunch event looks OK
  return bunch_index;

}

// ********************************************************
int MDTEventCheck::FindOneMEOneIntBunchIdx(AnaMDTEvent &event){
// ********************************************************

  // -------- Basic selection --------

  // Collect bunch -> interaction mapping using true information
  std::map<int,std::vector<int>> map_bunch_int_idx;
  for(int i = 0; i < event.n_int; i++){
    map_bunch_int_idx[event.vec_nu_bunch_idx[i]].push_back(i);
  }  

  // Loop over bunches where there are interactions
  for(auto &element : map_bunch_int_idx){

    // This bunch must have only one interaction
    // ME does not count as an interaction (it comes from a previous one)
    if(element.second.size() != 1) continue;

    // -------- Interaction requirement --------

    // Similar requirement as two interaction case
    if(!TrueInteractionCut(event,element.second[0])) continue;

    // -------- PMT hits requirement --------

    // Collect all PMT hits belong to this bunch
    MiscUtils::CollectBunchPMTHits(event,element.first,vec_PMT_hit_ID,vec_PMT_hit_OD);

    // ID hit number should be large enough
    if(vec_PMT_hit_ID.size() < 80) continue;

    // -------- ME PMT hits requirement --------

    // Must have ME contributions, and the ME should be produced by a previous interaction
    if(!PrevMEExistCut(event,element.first)) continue;

    // Bunch found
    return element.first;

  } // End of bunch loop

  // Not found
  return -1;

}

// ********************************************************
bool MDTEventCheck::TrueInteractionCut(AnaMDTEvent &event, int int_index){
// ********************************************************
  
  // Should be numu or nue
  if(std::abs(event.vec_nu_pdg[int_index]) != 12 && std::abs(event.vec_nu_pdg[int_index]) != 14) return false;

  // Should be CCQE interaction
  if(std::abs(event.vec_nu_neut_code[int_index]) != 1) return false;

  // Should have lepton
  if(!event.vec_trk_pri_lep[int_index]) return false;

  // Lepton should stop in ID
  if(!event.vec_trk_pri_lep_stop_ID[int_index]) return false;

  // Lepton should satisfy FV cuts
  if(!(event.vec_trk_pri_lep_towall[int_index] > 200 && event.vec_trk_pri_lep_dwall[int_index] > 100)) return false;

  // Lepton should have large enough momentum
  double mom_cut = std::abs(event.vec_nu_pdg[int_index]) == 14 ? 200 : 100;
  if(event.vec_trk_pri_lep_mom[int_index] < mom_cut) return false;

  return true;

}

// ********************************************************
bool MDTEventCheck::PrevMEExistCut(AnaMDTEvent &event, int bunch_index){
// ********************************************************

  int n_count_ME_hit = 0;

  // Loop over ID PMT hits for this bunch
  // The vector should be already filled
  for(auto *digi_hit : vec_PMT_hit_ID){

    bool is_ME_hit = false;
    // Loop over true photon hits contributed to this PMT hit
    for(int i : digi_hit->fPhotonIds){
      WCSimRootCherenkovHitTime *photon_hit = (WCSimRootCherenkovHitTime*)(event.wcsim_ID_event->fCherenkovHitTimes->At(i));
      if(!photon_hit) continue;

      // Check which true G4 track creates this photon hit
      int G4_trk_id = photon_hit->fParentSavedTrackID;
      if(G4_trk_id < 0) continue;
      // Get true G4 track
      WCSimRootTrack *G4_track = MiscUtils::GetG4TrkByID(G4_trk_id,event);
      if(!G4_track) continue;
      // Should be ME track
      if(!MiscUtils::IsG4MichelElectronTrk(G4_track)) continue;
      // The ME should come from interaction from previous bunch
      int ME_bunch = event.vec_nu_bunch_idx[event.vec_pe_int_idx->at(i)];
      if(ME_bunch >= bunch_index) continue;

      is_ME_hit = true;
    }

    if(is_ME_hit) n_count_ME_hit += 1;

  } // End of hit loop

  // Should exist enough ME hits for event display check
  return n_count_ME_hit >= 10;

}

// ********************************************************
void MDTEventCheck::FillOutputTree(AnaMDTEvent &event, int event_type){
// ********************************************************

  // Event type
  // 1 = two interaction, 2 = one ME + one interaction
  type = event_type;

  // ID PMT hits
  hits_ID_posX.clear();
  hits_ID_posY.clear();
  hits_ID_posZ.clear();
  hits_ID_charge.clear();
  hits_ID_intidx.clear();
  hits_ID_PDG.clear();
  for(auto *digi_hit : vec_PMT_hit_ID){

    // Position
    WCSimRootPMT *hit_PMT = (WCSimRootPMT*)(event.wcsim_geom)->fPMTArray->At(digi_hit->fTubeId-1);
    if(hit_PMT){
      hits_ID_posX.push_back(hit_PMT->fPosition[0]);
      hits_ID_posY.push_back(hit_PMT->fPosition[1]);
      hits_ID_posZ.push_back(hit_PMT->fPosition[2]);
    }
    else{
      hits_ID_posX.push_back(-1e6);
      hits_ID_posY.push_back(-1e6);
      hits_ID_posZ.push_back(-1e6);
    }

    // Charge
    hits_ID_charge.push_back(digi_hit->fQ);

    // Interaction index and PDG
    int int_index, true_pdg;
    GetPMTHitTrueInfo(event,digi_hit,true,int_index,true_pdg);
    hits_ID_intidx.push_back(int_index);
    hits_ID_PDG.push_back(true_pdg);
    
  } // End of hit loop

  // OD PMT hits
  hits_OD_posX.clear();
  hits_OD_posY.clear();
  hits_OD_posZ.clear();
  hits_OD_charge.clear();
  hits_OD_intidx.clear();
  hits_OD_PDG.clear();
  for(auto *digi_hit : vec_PMT_hit_OD){

    // Position
    WCSimRootPMT *hit_PMT = (WCSimRootPMT*)(event.wcsim_geom)->fODPMTArray->At(digi_hit->fTubeId-1);
    if(hit_PMT){
      hits_OD_posX.push_back(hit_PMT->fPosition[0]);
      hits_OD_posY.push_back(hit_PMT->fPosition[1]);
      hits_OD_posZ.push_back(hit_PMT->fPosition[2]);
    }
    else{
      hits_OD_posX.push_back(-1e6);
      hits_OD_posY.push_back(-1e6);
      hits_OD_posZ.push_back(-1e6);
    }

    // Charge
    hits_OD_charge.push_back(digi_hit->fQ);

    // Interaction index and PDG
    int int_index, true_pdg;
    GetPMTHitTrueInfo(event,digi_hit,false,int_index,true_pdg);
    hits_OD_intidx.push_back(int_index);
    hits_OD_PDG.push_back(true_pdg);
    
  } // End of hit loop

  // Fill the tree
  tout.Fill();

}

// ********************************************************
void MDTEventCheck::GetPMTHitTrueInfo(AnaMDTEvent &event, WCSimRootCherenkovDigiHit *digi_hit,
                                      bool is_ID, int &int_index, int &true_pdg){
// ********************************************************

  std::map<int,int> int_idx_count;
  std::map<int,int> true_PDG_count;

  // Loop over photon hit contributions
  for(int i : digi_hit->fPhotonIds){
    WCSimRootCherenkovHitTime *photon_hit = (WCSimRootCherenkovHitTime*)(event.wcsim_ID_event->fCherenkovHitTimes->At(i));
    if(!photon_hit) continue;

    // Count interaction index
    if(is_ID) int_idx_count[event.vec_pe_int_idx->at(i)] += 1;
    else int_idx_count[event.vec_pe_OD_int_idx->at(i)] += 1;

    // Count true PDG
    int G4_trk_id = photon_hit->fParentSavedTrackID;
    if(G4_trk_id < 0){
      true_PDG_count[-1] += 1; // Dark count
    }
    else{
      WCSimRootTrack *G4_track = MiscUtils::GetG4TrkByID(G4_trk_id,event);
      if(G4_track) true_PDG_count[G4_track->fIpnu] += 1;
    }
  } // End of hit loop

  // Interaction that gives maximum contribution
  int max_count = 0;
  for(auto element : int_idx_count){
    if(element.second > max_count){
      max_count = element.second;
      int_index = element.first;
    }
  }

  // True PDG that gives maximum contribution
  max_count = 0;
  for(auto element : true_PDG_count){
    if(element.second > max_count){
      max_count = element.second;
      true_pdg = element.first;
    }
  }

}