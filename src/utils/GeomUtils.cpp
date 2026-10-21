#include "utils/GeomUtils.h"

// ********************************************************
double GeomUtils::CalcToWallDis(TVector3 pos, TVector3 dir, bool apply_corr){
// ********************************************************

  // Outside ID
  if(CalcDWallDis(pos,apply_corr) < 0) return -1;

  // Correct the position if needed
  TVector3 rel_pos;
  if(apply_corr){
    rel_pos.SetXYZ(pos.X() - WCDetCentre.X(),pos.Y(),pos.Z() - WCDetCentre.Z());
  }
  else rel_pos = pos;

  double sZ = 0;
  if(dir.Y() > 0){
    sZ = (IDHalfLength - (rel_pos.Y() - IDCenterY)) / dir.Y();
  }
  else{
    sZ = (-1 * IDHalfLength - (rel_pos.Y() - IDCenterY)) / dir.Y();
  }

  if(std::pow(rel_pos.X() + sZ * dir.X(),2) + std::pow(rel_pos.Z() + sZ * dir.Z(),2)
     <= std::pow(IDRadius,2)) return sZ;

  double a = std::pow(dir.X(),2) + std::pow(dir.Z(),2);
  double b = 2 * (dir.X() * rel_pos.X() + dir.Z() * rel_pos.Z());
  double c = std::pow(rel_pos.X(),2) + std::pow(rel_pos.Z(),2) - std::pow(IDRadius,2);

  return (-1 * b + std::sqrt(b * b - 4 * a * c)) / (2 * a);

}

// ********************************************************
double GeomUtils::CalcDWallDis(TVector3 pos, bool apply_corr = false){
// ********************************************************

  // Correct the position if needed
  TVector3 rel_pos;
  if(apply_corr){
    rel_pos.SetXYZ(pos.X() - WCDetCentre.X(),pos.Y(),pos.Z() - WCDetCentre.Z());
  }
  else rel_pos = pos;

  double vtxRadius = std::sqrt(std::pow(rel_pos.X(),2) + std::pow(rel_pos.Z(),2));
  double dWallZ = IDHalfLength - std::fabs(rel_pos.Y() - IDCenterY);
  double dWallR = IDRadius - vtxRadius;

  // Result is negative if outside ID
  if(dWallZ < dWallR) return dWallZ;
  return dWallR;

}

// ********************************************************
bool GeomUtils::IsTrueTrackContained(double momentum, TVector3 pos, TVector3 dir, bool apply_corr){
// ********************************************************

  // TODO: The containment check needs Geant4 true trajectory information
  // This has to be propagated to fiTQun output

  // Get towall distance
  double tWall = CalcToWallDis(pos,dir,apply_corr);

  // TODO: This depends on particle type
  if(momentum > 2 * tWall) return false;
  return true;

}