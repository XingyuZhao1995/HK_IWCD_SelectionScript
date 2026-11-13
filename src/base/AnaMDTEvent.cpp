#include "base/AnaMDTEvent.h"

// -------- Public member functions --------

// ********************************************************
AnaMDTEvent::AnaMDTEvent(){
// ********************************************************

  wcsim_geom = nullptr;

  wcsim_ID_event = nullptr;
  wcsim_OD_event = nullptr;  

  vec_nu_pdg.clear();
  vec_nu_energy.clear();
  vec_nu_neut_code.clear();
  vec_nu_bunch_idx.clear();
  vec_nu_time.clear();
  vec_nu_pos.clear();

  vec_trk_pri_lep.clear();
  vec_trk_pri_lep_pdg.clear();
  vec_trk_pri_lep_mom.clear();
  vec_trk_pri_lep_dir.clear();
  vec_trk_pri_lep_stop_ID.clear();
  vec_trk_pri_lep_towall.clear();
  vec_trk_pri_lep_dwall.clear();

  vec_pe_int_idx = nullptr;
  vec_pe_OD_int_idx = nullptr;

}

// ********************************************************
AnaMDTEvent::~AnaMDTEvent(){
// ********************************************************

  wcsim_geom = nullptr;

  wcsim_ID_event = nullptr;
  wcsim_OD_event = nullptr;  

  vec_nu_pdg.clear();
  vec_nu_energy.clear();
  vec_nu_neut_code.clear();
  vec_nu_bunch_idx.clear();
  vec_nu_time.clear();
  vec_nu_pos.clear();

  vec_trk_pri_lep.clear();
  vec_trk_pri_lep_pdg.clear();
  vec_trk_pri_lep_mom.clear();
  vec_trk_pri_lep_dir.clear();
  vec_trk_pri_lep_stop_ID.clear();
  vec_trk_pri_lep_towall.clear();
  vec_trk_pri_lep_dwall.clear();

  vec_pe_int_idx = nullptr;
  vec_pe_OD_int_idx = nullptr;

}

// ********************************************************
void AnaMDTEvent::Reset(){
// ********************************************************

  wcsim_geom = nullptr;

  wcsim_ID_event = nullptr;
  wcsim_OD_event = nullptr;  

  vec_nu_pdg.clear();
  vec_nu_energy.clear();
  vec_nu_neut_code.clear();
  vec_nu_bunch_idx.clear();
  vec_nu_time.clear();
  vec_nu_pos.clear();

  vec_trk_pri_lep.clear();
  vec_trk_pri_lep_pdg.clear();
  vec_trk_pri_lep_mom.clear();
  vec_trk_pri_lep_dir.clear();
  vec_trk_pri_lep_stop_ID.clear();
  vec_trk_pri_lep_towall.clear();
  vec_trk_pri_lep_dwall.clear();
  
  vec_pe_int_idx = nullptr;
  vec_pe_OD_int_idx = nullptr;

}