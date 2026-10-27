#ifndef GEOMUTILS_H
#define GEOMUTILS_H

#include <TVector3.h>

namespace GeomUtils{

  // Later these settings should be read from the input file

  // WC detector geometry
  const double WCDetRadius = 350; // In cm
  const double WCDetHeight = 800; // In cm
  const TVector3 WCDetCentre(0,0,0);

  const double IDRadius = WCDetRadius;
  const double IDHalfLength = WCDetHeight / 2.0;
  const double IDCenterY = WCDetCentre.Y();

  // ----------------------------------------
  // Position utils

  // Correct position
  TVector3 CorrectPosition(TVector3 pos);

  // ----------------------------------------
  // Distance utils

  // Towall and dwall distances
  double CalcToWallDis(TVector3 pos, TVector3 dir, bool apply_corr = false);
  double CalcDWallDis(TVector3 pos, bool apply_corr = false);

  // ----------------------------------------
  // Containment utils
  
  // Point position containment
  bool IsPointIDContained(TVector3 pos, bool apply_corr = false);

  // General track containment
  bool IsTrkIDContainedByRange(double momentum, TVector3 pos, TVector3 dir, bool apply_corr = false);

};

#endif