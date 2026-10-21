#include "utils/SelectionUtils.h"

// ********************************************************
double SelectionUtils::ComputePIDemuRatio(AnafiTQunEvent &event){
// ********************************************************

  if(event.reco_1r_nllh.size() < 1) return -1e8;  

  return -1 * event.reco_1r_nllh[PIDCate::kElectron] + event.reco_1r_nllh[PIDCate::kMuon];

}