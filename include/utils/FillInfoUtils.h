#ifndef FILLINFOUTILS_H
#define FILLINFOUTILS_H

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"
#include "utils/GeomUtils.h"
#include "utils/CategoryUtils.h"

namespace FillInfoUtils{

  // Fill NEUT RooTracker vertex information
  void FillNEUTRooTrkVtxInfo(AnafiTQunEvent &event);

  // Fill Geant4 track information
  void FillG4TrkInfo(AnafiTQunEvent &event);

  // Fill OD hits information
  void FillODHitsInfo(AnafiTQunEvent &event);

};

#endif