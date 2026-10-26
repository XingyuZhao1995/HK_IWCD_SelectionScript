#include "base/AnafiTQunEvent.h"

// -------- Public member functions --------

// ********************************************************
AnafiTQunEvent::AnafiTQunEvent(){
// ********************************************************

  nrootrackervtx = nullptr;

  wcsim_event = nullptr;

  reco_1r_flag.clear();
  reco_1r_mom.clear();
  reco_1r_nllh.clear();
  reco_1r_pos.clear();
  reco_1r_dir.clear();

  reco_mr_ifit.clear();
  reco_mr_nring.clear();
  reco_mr_nllh.clear();

}

// ********************************************************
AnafiTQunEvent::~AnafiTQunEvent(){
// ********************************************************

  nrootrackervtx = nullptr;

  wcsim_event = nullptr;

  reco_1r_flag.clear();
  reco_1r_mom.clear();
  reco_1r_nllh.clear();
  reco_1r_pos.clear();
  reco_1r_dir.clear();

  reco_mr_ifit.clear();
  reco_mr_nring.clear();
  reco_mr_nllh.clear();

}

// ********************************************************
void AnafiTQunEvent::Reset(){
// ********************************************************  

  nrootrackervtx = nullptr;

  wcsim_event = nullptr;

  reco_1r_flag.clear();
  reco_1r_mom.clear();
  reco_1r_nllh.clear();
  reco_1r_pos.clear();
  reco_1r_dir.clear();

  reco_mr_ifit.clear();
  reco_mr_nring.clear();
  reco_mr_nllh.clear();

}