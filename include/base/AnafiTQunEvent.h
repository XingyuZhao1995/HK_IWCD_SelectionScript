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
  int nu_pdg;
  double nu_energy; // In MeV
  int nu_neut_code;

  // Geometry information
  TVector3 nu_vtx_pos; // In cm

  // Primary lepton information
  int nu_pri_lep_pdg;
  double nu_pri_lep_mom; // In MeV
  TVector3 nu_pri_lep_dir;

  // ----------------------------------------
  // Reconstruction information




};

#endif