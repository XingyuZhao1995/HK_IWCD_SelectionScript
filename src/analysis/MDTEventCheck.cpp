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

  std::cout << "Event " << event.event_id << std::endl;

  // -------- Basic selection --------

  // Collect bunch -> interaction mapping using true information
  std::map<int,std::vector<int>> map_bunch_int_idx;
  for(int i = 0; i < event.n_int; i++){
    std::cout << "(" << i << ", " << event.vec_nu_bunch_idx[i] << ") ";

    map_bunch_int_idx[event.vec_nu_bunch_idx[i]].push_back(i);
  }
  std::cout << std::endl;
  
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
  
  // Loop over true interactions
  for(int index : vec_bunch_int_index){
    if(!TrueInteractionCut(event,index)) return -1;
  }

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

      n_count_ME_hit += 1;
    }

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

  // Fill the tree
  tout.Fill();

}