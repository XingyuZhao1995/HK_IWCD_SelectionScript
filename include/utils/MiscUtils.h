#ifndef MISCUTILS_H
#define MISCUTILS_H

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"

namespace MiscUtils{

  // Get ID of the G4 track that contributes most PMT charges in a subevent
  int GetSubeventMaxG4TrkID(double peak_t0, AnafiTQunEvent &event);

  // Get G4 track by ID
  WCSimRootTrack* GetG4TrkByID(int G4_trk_id, AnafiTQunEvent &event);

};

#endif