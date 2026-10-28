#include "utils/FillInfoUtils.h"

// ********************************************************
void FillInfoUtils::FillNEUTRooTrkVtxInfo(AnafiTQunEvent &event){
// ********************************************************

  if(!event.nrootrackervtx) return;
  ND::NRooTrackerVtx *vertex = event.nrootrackervtx;

  event.nu_pdg = vertex->StdHepPdg[0];
  event.nu_energy = vertex->StdHepP4[0][3] * 1e3; // Convert into MeV
  event.nu_neut_code = vertex->EvtCode->GetString().Atoi();
  event.cate_type = CategoryUtils::GetInterCateType(event);

  TVector3 pos_tmp(vertex->EvtVtx[0],vertex->EvtVtx[1],vertex->EvtVtx[2]);
  pos_tmp *= 100.0; // Convert into cm
  event.nu_vtx_pos = GeomUtils::CorrectPosition(pos_tmp);

  TVector3 dir_tmp = pos_tmp - GeomUtils::BeamDecayPos;
  event.nu_dir = dir_tmp.Unit();

  /*
  int index_pri_lep = -1;
  for(int i = 1; i < vertex->StdHepN; i++){
    if(std::abs(vertex->StdHepPdg[i]) == 11 ||
       std::abs(vertex->StdHepPdg[i]) == 13 ||
       std::abs(vertex->StdHepPdg[i]) == 15){
      index_pri_lep = i;
      break;
    }
  }
  if(index_pri_lep > 0){
    event.nu_pri_lep_pdg = vertex->StdHepPdg[index_pri_lep];
    event.nu_pri_lep_dir.SetXYZ(vertex->StdHepP4[index_pri_lep][0],
                                vertex->StdHepP4[index_pri_lep][1],
                                vertex->StdHepP4[index_pri_lep][2]);
    event.nu_pri_lep_mom = event.nu_pri_lep_dir.Mag() * 1e3; // Convert into MeV/c
    if(event.nu_pri_lep_mom > 0){
      event.nu_pri_lep_dir *= (1e3 / event.nu_pri_lep_mom);
    }
  }
  */

}

// ********************************************************
void FillInfoUtils::FillG4TrkInfo(AnafiTQunEvent &event){
// ********************************************************

  if(!event.wcsim_ID_event) return;

  event.trk_npri_lep = 0;
  event.trk_npri_lep_thres = 0;
  event.trk_npri_p = 0;
  event.trk_npri_n = 0;
  event.trk_npri_piplus = 0;
  event.trk_npri_piplus_thres = 0;
  event.trk_npri_piminus = 0;
  event.trk_npri_piminus_thres = 0;
  event.trk_npri_pi0 = 0;
  event.trk_npri_other = 0;

  // Loop over Geant4 tracks
  for(int i = 0; i < event.wcsim_ID_event->fNtrack; i++){

    // Get the track
    WCSimRootTrack *track = (WCSimRootTrack*)(event.wcsim_ID_event->fTracks->At(i));
    if(!track) continue;

    // Only look at primary tracks
    if(track->fFlag < 0) continue;
    if(track->fParenttype != 0) continue;

    // Primary lepton
    if(std::abs(track->fIpnu) == 11 || std::abs(track->fIpnu) == 13 || std::abs(track->fIpnu) == 15){
      event.trk_npri_lep += 1;
      if(std::abs(track->fIpnu) == 11 && track->fP > 0.58) event.trk_npri_lep_thres += 1;
      else if(std::abs(track->fIpnu) == 13 && track->fP > 120) event.trk_npri_lep_thres += 1;

      event.trk_pri_lep_pdg = track->fIpnu;
      event.trk_pri_lep_mom = track->fP;
      event.trk_pri_lep_dir.SetXYZ(track->fDir[0],track->fDir[1],track->fDir[2]); // Already normalized

      // If track stops in ID
      TVector3 stop_pos(track->fStop[0],track->fStop[1],track->fStop[2]);
      event.trk_pri_lep_stop_ID = GeomUtils::IsPointIDContained(stop_pos);

      TVector3 start_pos(track->fStart[0],track->fStart[1],track->fStart[2]);
      event.trk_pri_lep_towall = GeomUtils::CalcToWallDis(start_pos,event.trk_pri_lep_dir);
      event.trk_pri_lep_dwall = GeomUtils::CalcDWallDis(start_pos);
    }
    // Other primary particles
    else if(track->fIpnu == 2212){
      event.trk_npri_p += 1;
    }
    else if(track->fIpnu == 2112){
      event.trk_npri_n += 1;
    }    
    else if(track->fIpnu == 211){
      event.trk_npri_piplus += 1;
      if(track->fP > 160) event.trk_npri_piplus_thres += 1;
    }       
    else if(track->fIpnu == -211){
      event.trk_npri_piminus += 1;
      if(track->fP > 160) event.trk_npri_piminus_thres += 1;
    } 
    else if(track->fIpnu == 111){
      event.trk_npri_pi0 += 1;
    }  
    else{
      event.trk_npri_other += 1;
    }

  } // End of track loop

}

// ********************************************************
void FillInfoUtils::FillODHitsInfo(AnafiTQunEvent &event){
// ********************************************************

  event.OD_nhit = 0;
  event.OD_charge_tot = 0;

  // Loop over OD PMT hits
  for(int i = 0; i < event.wcsim_OD_event->fNcherenkovdigihits; i++){

    // Get the hit
    WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)(event.wcsim_OD_event->fCherenkovDigiHits->At(i));
    if(!hit) continue;

    // Get hit information
    event.OD_nhit += 1;
    event.OD_charge_tot += hit->fQ;

  } // End of hit loop

}