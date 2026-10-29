#include "utils/GeomUtils.h"

// ********************************************************
TVector3 GeomUtils::CorrectPosition(TVector3 pos){
// ********************************************************

  TVector3 corr_pos(pos.X() - WCDetCentre.X(),pos.Y(),pos.Z() - WCDetCentre.Z());
  
  return corr_pos;

}

// ********************************************************
double GeomUtils::CalcOffAxisAngle(TVector3 pos){
// ********************************************************

  TVector3 dir_tmp = pos - BeamDecayPos;
  dir_tmp = dir_tmp.Unit();

  return TMath::ACos(dir_tmp.Dot(OnAxisNuDir)) * 180.0 / TMath::Pi();

}

// ********************************************************
double GeomUtils::CalcIncludedAngle(TVector3 dir_1, TVector3 dir_2){
// ********************************************************

  dir_1 = dir_1.Unit();
  dir_2 = dir_2.Unit();

  return TMath::ACos(dir_1.Dot(dir_2)) * 180.0 / TMath::Pi();

}

// ********************************************************
double GeomUtils::CalcIncludedCosAng(TVector3 dir_1, TVector3 dir_2){
// ********************************************************

  dir_1 = dir_1.Unit();
  dir_2 = dir_2.Unit();

  return dir_1.Dot(dir_2);

}

// ********************************************************
double GeomUtils::CalcToWallDis(TVector3 pos, TVector3 dir){
// ********************************************************

  // Outside ID
  if(CalcDWallDis(pos) < 0) return -1;

  double sZ = 0;
  if(dir.Y() > 0){
    sZ = (IDHalfLength - (pos.Y() - IDCenterY)) / dir.Y();
  }
  else{
    sZ = (-1 * IDHalfLength - (pos.Y() - IDCenterY)) / dir.Y();
  }

  if(std::pow(pos.X() + sZ * dir.X(),2) + std::pow(pos.Z() + sZ * dir.Z(),2)
     <= std::pow(IDRadius,2)) return sZ;

  double a = std::pow(dir.X(),2) + std::pow(dir.Z(),2);
  double b = 2 * (dir.X() * pos.X() + dir.Z() * pos.Z());
  double c = std::pow(pos.X(),2) + std::pow(pos.Z(),2) - std::pow(IDRadius,2);

  return (-1 * b + std::sqrt(b * b - 4 * a * c)) / (2 * a);

}

// ********************************************************
double GeomUtils::CalcDWallDis(TVector3 pos){
// ********************************************************

  double vtxRadius = std::sqrt(std::pow(pos.X(),2) + std::pow(pos.Z(),2));
  double dWallZ = IDHalfLength - std::fabs(pos.Y() - IDCenterY);
  double dWallR = IDRadius - vtxRadius;

  // Result is negative if outside ID
  if(dWallZ < dWallR) return dWallZ;
  return dWallR;

}

// ********************************************************
bool GeomUtils::IsPointIDContained(TVector3 pos){
// ********************************************************

  double radius = std::sqrt(std::pow(pos.X(),2) + std::pow(pos.Z(),2));
  double height = std::fabs(pos.Y() - IDCenterY);

  if(radius < IDRadius && height < IDHalfLength) return true;
  return false;

}

// ********************************************************
bool GeomUtils::IsTrkIDContainedByRange(double momentum, TVector3 pos, TVector3 dir){
// ********************************************************

  // Get towall distance
  double tWall = CalcToWallDis(pos,dir);

  // This depends on particle type
  if(momentum > 2 * tWall) return false;
  return true;

}