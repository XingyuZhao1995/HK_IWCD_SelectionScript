#ifndef MISCUTILS_H
#define MISCUTILS_H

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"
#include "utils/CategoryUtils.h"
#include "utils/GeomUtils.h"

using namespace CategoryUtils;

namespace MiscUtils{

  // All units in MeV/c2
  const double MuonMass = 105.658;
  const double ElectronMass = 0.511;

  const double ProtonMass = 938.272;
  const double NeutronMass = 939.565;

  const double Eb_Neutron_O = 26; // Mean approx.

  // ----------------------------------------
  // Geant4 utils

  // Get ID of the G4 track that contributes most PMT charges in a subevent
  int GetSubeventMaxG4TrkID(double peak_t0, AnafiTQunEvent &event);

  // Get G4 track by ID
  WCSimRootTrack* GetG4TrkByID(int G4_trk_id, AnafiTQunEvent &event);

  // Get parent interaction information
  int GetG4TrkParInterInfo(WCSimRootTrack *track);

  // ----------------------------------------
  // Neutrino energy utils

  // Calculate neutrino energy
  double CalcEnuNumuCCQE(AnafiTQunEvent &event);

};

#endif