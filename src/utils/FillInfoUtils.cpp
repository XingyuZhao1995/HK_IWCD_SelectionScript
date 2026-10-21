#include "utils/FillInfoUtils.h"

// ********************************************************
void FillInfoUtils::FillNEUTRooTrkVtxInfo(AnafiTQunEvent &event){
// ********************************************************

  if(!event.nrootrackervtx) return;
  ND::NRooTrackerVtx *vertex = event.nrootrackervtx;

  event.nu_pdg = vertex->StdHepPdg[0];
  event.nu_energy = vertex->StdHepP4[0][3] * 1e3; // Convert into MeV
  event.nu_neut_code = vertex->EvtCode->GetString().Atoi();

  event.nu_vtx_pos.SetXYZ(vertex->EvtVtx[0],vertex->EvtVtx[1],vertex->EvtVtx[2]);
  event.nu_vtx_pos *= 100.0; // Convert into cm

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

}