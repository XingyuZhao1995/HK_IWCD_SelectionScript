#ifndef ANAMDTEVENT_H
#define ANAMDTEVENT_H

#include <algorithm>

#include <TVector3.h>

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"

// A MDT event class used for analysis
class AnaMDTEvent{

public:

  AnaMDTEvent();
  ~AnaMDTEvent();

  // Reset the event
  void Reset();  

  // ----------------------------------------
  // General information

  int run = -1;
  int subrun = -1;
  int event_id = -1;

  // General pointer
  WCSimRootTrigger *wcsim_ID_event;
  WCSimRootTrigger *wcsim_OD_event;

  // ----------------------------------------
  // Pile-up information

  // How many interactions in this event
  int n_int = 0;

  // ----------------------------------------
  // Interaction information

  std::vector<int> vec_nu_pdg;  
  std::vector<double> vec_nu_energy;
  std::vector<int> vec_nu_neut_code;
  std::vector<int> vec_nu_bunch_idx;
  std::vector<double> vec_nu_time;
  std::vector<TVector3> vec_nu_pos;

  // ----------------------------------------
  // True track information

  int n_trk = 0;
  UInt_t *trk_int_idx;

  // Primary lepton information
  std::vector<WCSimRootTrack*> vec_trk_pri_lep;
  std::vector<int> vec_trk_pri_lep_pdg;
  std::vector<double> vec_trk_pri_lep_mom;
  std::vector<TVector3> vec_trk_pri_lep_dir;
  std::vector<bool> vec_trk_pri_lep_stop_ID;
  std::vector<double> vec_trk_pri_lep_towall;
  std::vector<double> vec_trk_pri_lep_dwall;

  // ----------------------------------------
  // True hit information

  std::vector<int> *vec_pe_int_idx;
  std::vector<int> *vec_pe_OD_int_idx;

};

#endif