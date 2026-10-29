#ifndef GEOMUTILS_H
#define GEOMUTILS_H

#include <TVector3.h>
#include <TMath.h>

namespace GeomUtils{

  // Later these settings should be read from the input file

  // WC detector geometry
  const double WCDetRadius = 350; // In cm
  const double WCDetHeight = 800; // In cm
  const TVector3 WCDetCentre(0,0,0);

  const double IDRadius = WCDetRadius;
  const double IDHalfLength = WCDetHeight / 2.0;
  const double IDCenterY = WCDetCentre.Y();

  // Beam (neutrino parent) decay point
  const TVector3 BeamDecayPos(0,-2.675413*100.,-42.28534*100.);
  // On-axis neutrino beam direction
  const TVector3 OnAxisNuDir(0,-1.0*TMath::Sin(0.063478),TMath::Cos(0.063478));

  // ----------------------------------------
  // Position utils

  // Correct position
  TVector3 CorrectPosition(TVector3 pos);

  // ----------------------------------------
  // Direction utils

  // Off-axis angle
  double CalcOffAxisAngle(TVector3 pos);

  // General angle between two directions
  double CalcIncludedAngle(TVector3 dir_1, TVector3 dir_2);
  double CalcIncludedCosAng(TVector3 dir_1, TVector3 dir_2);

  // ----------------------------------------
  // Distance utils

  // Towall and dwall distances
  double CalcToWallDis(TVector3 pos, TVector3 dir);
  double CalcDWallDis(TVector3 pos);

  // ----------------------------------------
  // Containment utils
  
  // Point position containment
  bool IsPointIDContained(TVector3 pos);

  // General track containment
  bool IsTrkIDContainedByRange(double momentum, TVector3 pos, TVector3 dir);

};

#endif