#ifndef ANAFITQUNEVENT_H
#define ANAFITQUNEVENT_H

#include <algorithm>

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

  
  // Geometry information


  // Primary particle information


  // ----------------------------------------
  // Reconstruction information




};

#endif