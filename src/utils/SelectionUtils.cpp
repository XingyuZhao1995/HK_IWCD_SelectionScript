#include "utils/SelectionUtils.h"

// ********************************************************
double SelectionUtils::ComputePIDemuRatio(AnafiTQunEvent &event){
// ********************************************************

  if(event.reco_1r_nllh.size() < 1) return -1e8;  

  return -1 * event.reco_1r_nllh[PIDCate::kElectron] + event.reco_1r_nllh[PIDCate::kMuon];

}

// ********************************************************
double SelectionUtils::GetMinNegLLH1Ring(AnafiTQunEvent &event, PIDCate par_type){
// ********************************************************

  return par_type == PIDCate::kOther ? event.reco_pi0_nllh : event.reco_1r_nllh[par_type];

}

// ********************************************************
double SelectionUtils::GetMinNegLLH2Ring(AnafiTQunEvent &event){
// ********************************************************

  double min_2ring = 1e8;
  for(int i = 0; i < event.reco_mr_nfit; i++){
    if(event.reco_mr_nring[i] == 2){
      if(event.reco_mr_nllh[i] < min_2ring) min_2ring = event.reco_mr_nllh[i];
    }
  }

  return min_2ring;

}

// ********************************************************
double SelectionUtils::GetMinNegLLH3Ring(AnafiTQunEvent &event){
// ********************************************************

  double min_3ring = 1e8;
  for(int i = 0; i < event.reco_mr_nfit; i++){
    if(event.reco_mr_nring[i] == 3){
      if(event.reco_mr_nllh[i] < min_3ring) min_3ring = event.reco_mr_nllh[i];
    }
  }

  return min_3ring;

}

// ********************************************************
int SelectionUtils::GetNRecoRing(AnafiTQunEvent &event, PIDCate par_type){
// ********************************************************

  // TODO: Understand why counting rings should be like this
  double cut_one = 0;
  double cut_two = 0;
  if(par_type == PIDCate::kElectron){
    cut_one = 12 + 0.6091 * event.reco_1r_mom[par_type];
    if(cut_one > 300) cut_one = 300;
  }
  else if(par_type == PIDCate::kMuon){
    cut_one = 200;
  }
  
  double min_1ring = GetMinNegLLH1Ring(event,par_type);
  double min_2ring = GetMinNegLLH2Ring(event);
  double min_3ring = GetMinNegLLH3Ring(event);

  if(par_type == PIDCate::kElectron){
    if((min_1ring - min_2ring) < cut_one) return 1;
    else return 2;
  }
  else if(par_type == PIDCate::kMuon){
    if((min_1ring - min_2ring) < cut_one) return 1;
    else if((min_2ring - min_3ring) < cut_two) return 2;
    else return 3;
  }
  
  return 0;

}