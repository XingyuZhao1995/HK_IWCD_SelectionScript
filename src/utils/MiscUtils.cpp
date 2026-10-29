#include "utils/MiscUtils.h"

// ********************************************************
int MiscUtils::GetSubeventMaxG4TrkID(double peak_t0, AnafiTQunEvent &event){
// ********************************************************

  std::map<int,int> G4_trk_count;

  // Define a 50 ns time window
  double t_min = peak_t0 - 50;
  double t_max = peak_t0 + 50;

  // Loop over PMT hits
  for(int i = 0; i < event.wcsim_ID_event->fNcherenkovdigihits; i++){

    // Get the hit
    WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(event.wcsim_ID_event->fCherenkovDigiHits->At(i));
    if(!hit) continue;

    // Only look at hit within the time window
    if(hit->fT < t_min || hit->fT > t_max) continue;

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
  if(std::abs(track->fIpnu) == 11){
    // Electron, produced by muon decay
    // To be more precise this should be checked with fCreatorProcess,
    // but need to check first if this is the same process code from Geant4
    if(std::abs(track->fParenttype) == 13) return 2;
    // Others
    else return 3;
  }
  
  // Others
  return 4;

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