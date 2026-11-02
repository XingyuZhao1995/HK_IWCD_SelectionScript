#include "base/AnafiTQunEvent.h"

// -------- Public member functions --------

// ********************************************************
AnafiTQunEvent::AnafiTQunEvent(){
// ********************************************************

  nrootrackervtx = nullptr;

  wcsim_ID_event = nullptr;
  wcsim_OD_event = nullptr;

  reco_subeve_max_PDG.clear();
  reco_subeve_max_pri.clear();

  trk_pri_lep = nullptr;

  trk_pri_p.clear();
  trk_pri_n.clear();
  trk_pri_piplus.clear();
  trk_pri_piminus.clear();
  trk_pri_pi0.clear();
  trk_pri_other.clear();

  trk_ME_pri_lep = nullptr;

  reco_1r_flag.clear();
  reco_1r_mom.clear();
  reco_1r_nllh.clear();
  reco_1r_pos.clear();
  reco_1r_dir.clear();

  reco_mr_ifit.clear();
  reco_mr_nring.clear();
  reco_mr_nllh.clear();

  nu_vtx_pos.SetXYZ(0,0,0);
  nu_dir.SetXYZ(0,0,1);
  trk_pri_lep_dir.SetXYZ(0,0,1);

}

// ********************************************************
AnafiTQunEvent::~AnafiTQunEvent(){
// ********************************************************

  nrootrackervtx = nullptr;

  wcsim_ID_event = nullptr;
  wcsim_OD_event = nullptr;

  reco_subeve_max_PDG.clear();
  reco_subeve_max_pri.clear();

  trk_pri_lep = nullptr;

  trk_pri_p.clear();
  trk_pri_n.clear();
  trk_pri_piplus.clear();
  trk_pri_piminus.clear();
  trk_pri_pi0.clear();
  trk_pri_other.clear();

  trk_ME_pri_lep = nullptr;

  reco_1r_flag.clear();
  reco_1r_mom.clear();
  reco_1r_nllh.clear();
  reco_1r_pos.clear();
  reco_1r_dir.clear();

  reco_mr_ifit.clear();
  reco_mr_nring.clear();
  reco_mr_nllh.clear();

  nu_vtx_pos.SetXYZ(0,0,0);
  nu_dir.SetXYZ(0,0,1);
  trk_pri_lep_dir.SetXYZ(0,0,1);

}

// ********************************************************
void AnafiTQunEvent::Reset(){
// ********************************************************  

  nrootrackervtx = nullptr;

  wcsim_ID_event = nullptr;
  wcsim_OD_event = nullptr;

  reco_subeve_max_PDG.clear();
  reco_subeve_max_pri.clear();

  trk_pri_lep = nullptr;

  trk_pri_p.clear();
  trk_pri_n.clear();
  trk_pri_piplus.clear();
  trk_pri_piminus.clear();
  trk_pri_pi0.clear();
  trk_pri_other.clear();

  trk_ME_pri_lep = nullptr;

  reco_1r_flag.clear();
  reco_1r_mom.clear();
  reco_1r_nllh.clear();
  reco_1r_pos.clear();
  reco_1r_dir.clear();

  reco_mr_ifit.clear();
  reco_mr_nring.clear();
  reco_mr_nllh.clear();

  nu_vtx_pos.SetXYZ(0,0,0);
  nu_dir.SetXYZ(0,0,1);
  trk_pri_lep_dir.SetXYZ(0,0,1);

}