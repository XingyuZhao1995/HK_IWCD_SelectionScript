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
  // Vertex information

  // General pointer
  ND::NRooTrackerVtx *nrootrackervtx;

  // Interaction information
  int nu_pdg = 0;
  double nu_energy = -999; // In MeV
  int nu_neut_code = -1;

  // Geometry information
  TVector3 nu_vtx_pos; // In cm

  // Primary lepton information
  int nu_pri_lep_pdg = 0;
  double nu_pri_lep_mom = -999; // In MeV
  TVector3 nu_pri_lep_dir;

  // ----------------------------------------
  // Reconstruction information

  // Tag to indicate if subevent exists
  bool reco_tag = true;

  // Subevent information
  int reco_nsubeve = -1;

  // Information in max subevent
  // (Single ring)
  std::vector<int> reco_1r_flag;
  std::vector<double> reco_1r_mom; // In MeV/c
  std::vector<double> reco_1r_nllh;
  std::vector<TVector3> reco_1r_pos; // In cm
  std::vector<TVector3> reco_1r_dir;

  // (Multi ring)
  int reco_mr_nfit;
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