#include "utils/MiscUtils.h"

// ********************************************************
int MiscUtils::GetSubeventMaxG4TrkID(AnafiTQunEvent &event, double peak_t0, TVector3 vtx_prefit){
// ********************************************************

  std::map<int,int> G4_trk_count;

  // Define a 90 ns time window
  // This only looks at the contribution to the peak
  // Checked from fiTQun, in principle the first peak in a time window should use all hits
  // except the hits used by later peaks ([-30,60] ns for each), but for simplicity here
  // uses the same interval for the first peak as well
  double t_min = peak_t0 - 30;
  double t_max = peak_t0 + 60;

  // Loop over PMT hits
  for(int i = 0; i < event.wcsim_ID_event->fNcherenkovdigihits; i++){

    // Get the hit
    WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(event.wcsim_ID_event->fCherenkovDigiHits->At(i));
    if(!hit) continue;

    // Hit time has to be TOF corrected
    WCSimRootPMT *hit_PMT = (WCSimRootPMT*)(event.wcsim_geom)->fPMTArray->At(hit->fTubeId-1);
    TVector3 hit_pos(hit_PMT->fPosition[0],hit_PMT->fPosition[1],hit_PMT->fPosition[2]);
    double hit_time = hit->fT - (hit_pos - vtx_prefit).Mag() * 1.38 / 29.9792458; // Formula copied from fiTQun

    // Only look at hit within the time window
    if(hit_time < t_min || hit_time > t_max) continue;

    // Loop over photon hits attached to this PMT hit
    for(int j : hit->fPhotonIds){

      // Get the hit
      WCSimRootCherenkovHitTime *photon_hit = (WCSimRootCherenkovHitTime*)(event.wcsim_ID_event->fCherenkovHitTimes->At(j));
      if(!photon_hit) continue;

      // Check which true G4 track creates this photon hit
      int G4_trk_id = photon_hit->fParentSavedTrackID;
      // Skip dark noise
      if(G4_trk_id < 0) continue;
      
      // Accumulate track count
      G4_trk_count[G4_trk_id] += 1;

    } // End of photon hit loop

  } // End of PMT hit loop

  // Find the G4 track contributes most charges
  int max_index = -1;
  int max_count = 0;
  for(auto element : G4_trk_count){
    if(element.second > max_count){
      max_count = element.second;
      max_index = element.first;
    }
  }

  return max_index;

}

// ********************************************************
WCSimRootTrack* MiscUtils::GetG4TrkByID(int G4_trk_id, AnafiTQunEvent &event){
// ********************************************************

  // NOTE: The true track array for ID event is shared by both ID and OD hits

  WCSimRootTrack *track_need = nullptr;

  // Invalid track ID
  if(G4_trk_id < 0) return track_need;

  // Loop over G4 tracks
  for(int i = 0; i < event.wcsim_ID_event->fNtrack; i++){

    // Get the track
    WCSimRootTrack *track = (WCSimRootTrack*)(event.wcsim_ID_event->fTracks->At(i));
    if(!track) continue;

    // Whether ID matches
    if(track->fId == G4_trk_id){
      track_need = track;
      break;
    }

  } // End of track loop

  return track_need;

}

// ********************************************************
WCSimRootTrack* MiscUtils::GetG4TrkByID(int G4_trk_id, AnaMDTEvent &event){
// ********************************************************

  // NOTE: The true track array for ID event is shared by both ID and OD hits

  WCSimRootTrack *track_need = nullptr;

  // Invalid track ID
  if(G4_trk_id < 0) return track_need;

  // Loop over G4 tracks
  for(int i = 0; i < event.wcsim_ID_event->fNtrack; i++){

    // Get the track
    WCSimRootTrack *track = (WCSimRootTrack*)(event.wcsim_ID_event->fTracks->At(i));
    if(!track) continue;

    // Whether ID matches
    if(track->fId == G4_trk_id){
      track_need = track;
      break;
    }

  } // End of track loop

  return track_need;

}

// ********************************************************
int MiscUtils::GetG4TrkParInterInfo(WCSimRootTrack *track){
// ********************************************************

  if(!track) return -1;

  // Primary track
  if(track->fParenttype == 0) return 1;

  // Non-primary track
  // For the moment only look at electron
  if(std::abs(track->fIpnu) == 11){
    // Produced by muon decay
    if(IsG4MichelElectronTrk(track)) return 2;
    // Others
    else return 3;
  }
  
  // Others
  return 4;

}

// ********************************************************
bool MiscUtils::IsG4MichelElectronTrk(WCSimRootTrack *track){
// ********************************************************

  // For enumerate of fCreatorProcess check WCSim/include/WCSimEnumerations.hh
  // Some useful values for electron production:
  // 4 = Compton, 10 = gamma conversion
  // 13 = mu- capture at rest, 16 = decay

  // Should be electron
  if(std::abs(track->fIpnu) != 11) return false;

  // Electron case
  if(track->fIpnu == 11){
    // Parent should muon and with same charge
    if(track->fParenttype != 13) return false;
    // Should be produced by decay or mu- capture at rest
    if(track->fCreatorProcess != 13 && track->fCreatorProcess != 16) return false;
    // Then it is Michel electron
    return true;
  }
  // Positron case
  else{
    // Parent should muon and with same charge
    if(track->fParenttype != -13) return false; 
    // Should be produced by decay (no capture here) 
    if(track->fCreatorProcess != 16) return false;
    // Then it is Michel electron
    return true;    
  }

  return false;

}

// ********************************************************
double MiscUtils::CalcEnuNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  double mn_eff = NeutronMass - Eb_Neutron_O;
  double p_mu = event.reco_1r_mom[PIDCate::kMuon];
  double E_mu = std::sqrt(p_mu * p_mu + MuonMass * MuonMass);
  double cos_mu = GeomUtils::CalcIncludedCosAng(
                  event.reco_1r_dir[PIDCate::kMuon],event.reco_1r_pos[PIDCate::kMuon]-GeomUtils::BeamDecayPos);

  double numerator = MuonMass * MuonMass + mn_eff * mn_eff - ProtonMass * ProtonMass
                     - 2 * E_mu * mn_eff;
  double denominator = 2 * (E_mu - p_mu * cos_mu - mn_eff);

  return numerator / denominator;

}

// ********************************************************
void MiscUtils::CollectBunchPMTHits(AnaMDTEvent &event, int bunch_index, 
                         std::vector<WCSimRootCherenkovDigiHit*> &vec_PMT_hit_ID,
                         std::vector<WCSimRootCherenkovDigiHit*> &vec_PMT_hit_OD){
// ********************************************************

  vec_PMT_hit_ID.clear();
  vec_PMT_hit_OD.clear();

  // Calculate time interval
  double t_min = BunchT0 + bunch_index * BunchTIntv - BunchTSeleIntv;
  double t_max = BunchT0 + bunch_index * BunchTIntv + BunchTSeleIntv;

  // Loop over ID digitized hits
  for(int i = 0; i < event.wcsim_ID_event->fNcherenkovdigihits; i++){

    // Get the hit
    WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(event.wcsim_ID_event)->fCherenkovDigiHits->At(i);
    if(!hit) continue;

    // Check hit time
    if(hit->fT < t_min || hit->fT > t_max) continue;

    // Record hit
    vec_PMT_hit_ID.push_back(hit);

  } // End of hit loop

  // Loop over OD digitized hits
  for(int i = 0; i < event.wcsim_OD_event->fNcherenkovdigihits; i++){

    // Get the hit
    WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(event.wcsim_OD_event)->fCherenkovDigiHits->At(i);
    if(!hit) continue;

    // Check hit time
    // NOTE: OD hits usually have larger time delays, maybe the timing cut
    // should be larger for OD hits
    if(hit->fT < t_min || hit->fT > t_max) continue;

    // Record hit
    vec_PMT_hit_OD.push_back(hit);

  } // End of hit loop

}

// ********************************************************
void MiscUtils::ReadRunNumberFromFileName(std::string file_name, int &run, int &subrun){
// ********************************************************

  std::size_t slash = file_name.find_last_of('/');
  std::string base = (slash == std::string::npos) ? file_name : file_name.substr(slash + 1);

  std::regex re("(\\d+)-(\\d+)");
  std::smatch m;
  if(!std::regex_search(base, m, re)) return;

  run = std::stoi(m[1].str());
  subrun = std::stoi(m[2].str());

}