#ifndef ANAFITQUNEVENT_H
#define ANAFITQUNEVENT_H

#include <algorithm>

#include <TVector3.h>

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"

// A fiTQun event class used for analysis
class AnafiTQunEvent{

public:

  AnafiTQunEvent();
  ~AnafiTQunEvent();

  // Reset the event
  void Reset();  

  // ----------------------------------------
  // True vertex information

  // General pointer
  ND::NRooTrackerVtx *nrootrackervtx;

  // Interaction information
  int nu_pdg = 0;
  double nu_energy = -999; // In MeV
  int nu_neut_code = -1;
  int cate_type = -1;

  // Geometry information
  TVector3 nu_vtx_pos; // In cm
  TVector3 nu_dir;

  // ----------------------------------------
  // True track information

  // General pointer
  WCSimRootTrigger *wcsim_ID_event;
  WCSimRootTrigger *wcsim_OD_event;

  // Primary lepton information
  int trk_pri_lep_pdg = 0;
  double trk_pri_lep_mom = -999; // In MeV
  TVector3 trk_pri_lep_dir;  
  bool trk_pri_lep_stop_ID = false;
  double trk_pri_lep_towall = -999;
  double trk_pri_lep_dwall = -999;

  // Primary track count
  // (_thres means above water Cherenkov threshold)
  int trk_npri_lep = -1;
  int trk_npri_lep_thres = -1;
  int trk_npri_p = -1;
  int trk_npri_n = -1;
  int trk_npri_piplus = -1;
  int trk_npri_piplus_thres = -1;
  int trk_npri_piminus = -1;
  int trk_npri_piminus_thres = -1;
  int trk_npri_pi0 = -1;
  int trk_npri_other = -1;

  // ----------------------------------------
  // PMT hit information

  // ID

  // OD
  // (General information)
  int OD_nhit = -1;
  double OD_charge_tot = -999;

  // ----------------------------------------
  // Reconstruction information

  // Tag to indicate if subevent exists
  bool reco_tag = true;

  // Subevent information
  int reco_nsubeve = -1;
  int reco_subeve_max_index = -1;
  // (Particle that contributes most PMT hit charges in each subevent)
  std::vector<int> reco_subeve_max_PDG;
  std::vector<int> reco_subeve_max_pri; // 1 (primary), 2 (electron from muon decay), 3 (electron from other sources), 4 (other secondary)

  // Information in max subevent
  // (Single ring)
  std::vector<int> reco_1r_flag;
  std::vector<double> reco_1r_mom; // In MeV/c
  std::vector<double> reco_1r_nllh;
  std::vector<TVector3> reco_1r_pos; // In cm
  std::vector<TVector3> reco_1r_dir;

  // (Multi ring)
  int reco_mr_nfit = -1;
  std::vector<int> reco_mr_ifit;
  std::vector<int> reco_mr_nring;
  std::vector<double> reco_mr_nllh;

  // Pi0 tagging information
  double reco_pi0_nllh = -1;

  // ----------------------------------------
  // Selection information

  // Tag to indicate if this event passed the selection
  bool passed_selection = false;

};

#endif