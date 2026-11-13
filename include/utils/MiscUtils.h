#ifndef MISCUTILS_H
#define MISCUTILS_H

#include <regex>

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"
#include "base/AnaMDTEvent.h"
#include "utils/CategoryUtils.h"
#include "utils/GeomUtils.h"

using namespace CategoryUtils;

namespace MiscUtils{

  // Mass constants
  // All units in MeV/c2
  const double MuonMass = 105.658;
  const double ElectronMass = 0.511;

  const double ProtonMass = 938.272;
  const double NeutronMass = 939.565;

  const double Eb_Neutron_O = 26; // Mean approx.

  // Momentum Cherenkov threshold
  // Give 30 MeV/c margin above the normal threshold
  // All units in MeV/c
  const double MuonMomCheThres = 150;
  const double EleMomCheThres = 30;
  const double PionMomCheThres = 190;

  // Bunch timing constants
  const int NBunch = 8;
  const double BunchT0 = 0; // In ns
  const double BunchTIntv = 560;
  const double BunchTSeleIntv = 125; // For selection

  // ----------------------------------------
  // Geant4 utils

  // Get ID of the G4 track that contributes most PMT charges in a subevent
  int GetSubeventMaxG4TrkID(AnafiTQunEvent &event, double peak_t0, TVector3 vtx_prefit);

  // Get G4 track by ID
  WCSimRootTrack* GetG4TrkByID(int G4_trk_id, AnafiTQunEvent &event);
  WCSimRootTrack* GetG4TrkByID(int G4_trk_id, AnaMDTEvent &event, bool is_ID = true);

  // Get parent interaction information
  int GetG4TrkParInterInfo(WCSimRootTrack *track);
  // Check if the track is Michel electron
  bool IsG4MichelElectronTrk(WCSimRootTrack *track);
  
  // ----------------------------------------
  // Neutrino energy utils

  // Calculate neutrino energy
  double CalcEnuNumuCCQE(AnafiTQunEvent &event);

  // ----------------------------------------
  // Bunch utils

  // Collect all PMT hits in a bunch
  void CollectBunchPMTHits(AnaMDTEvent &event, int bunch_index, 
                           std::vector<WCSimRootCherenkovDigiHit*> &vec_PMT_hit_ID,
                           std::vector<WCSimRootCherenkovDigiHit*> &vec_PMT_hit_OD);

  // ----------------------------------------
  // Other utils

  // Read run and subrun numbers from file name
  void ReadRunNumberFromFileName(std::string file_name, int &run, int &subrun);

};

#endif