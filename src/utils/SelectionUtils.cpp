#include "utils/SelectionUtils.h"

// ********************************************************
bool SelectionUtils::IsTrueNumuCCQESignal(AnafiTQunEvent &event){
// ********************************************************

  // Interaction type
  bool cut_inte = (event.cate_type == 0);

  // Lepton containment
  bool cut_contain = event.trk_pri_lep_stop_ID;

  // FV
  bool cut_FV = (event.trk_pri_lep_towall > 200) && (event.trk_pri_lep_dwall > 100);

  // Momentum
  bool cut_momentum = (event.trk_pri_lep_mom > 200);

  return cut_inte && cut_contain && cut_FV && cut_momentum;

}

// ********************************************************
bool SelectionUtils::IsTrueNueCCQESignal(AnafiTQunEvent &event){
// ********************************************************

  // Interaction type
  bool cut_inte = (event.cate_type == 2);

  // Lepton containment
  bool cut_contain = event.trk_pri_lep_stop_ID;

  // FV
  bool cut_FV = (event.trk_pri_lep_towall > 200) && (event.trk_pri_lep_dwall > 100);

  // Momentum
  bool cut_momentum = (event.trk_pri_lep_mom > 100);

  return cut_inte && cut_contain && cut_FV && cut_momentum;

}

// ********************************************************
bool SelectionUtils::PassODVetoNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  // OD PMT hit number
  if(event.OD_nhit > 5) return false;

  // OD PMT hit total charge
  if(event.OD_charge_tot > 10) return false;

  return true;

}

// ********************************************************
double SelectionUtils::GetMinNegLLH1Ring(AnafiTQunEvent &event, PIDCate par_type){
// ********************************************************

  return par_type == PIDCate::kRest ? event.reco_pi0_nllh : event.reco_1r_nllh[par_type];

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
int SelectionUtils::GetNRecoRingRef(AnafiTQunEvent &event, PIDCate par_type){
// ********************************************************

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

// ********************************************************
int SelectionUtils::GetNRecoRingNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  double min_1ring = GetMinNegLLH1Ring(event,PIDCate::kMuon);
  double min_2ring = GetMinNegLLH2Ring(event);
  double ring_21 = min_1ring - min_2ring;

  if(ring_21 < 400) return 1;
  else return 2;

  return 0;

}

// ********************************************************
bool SelectionUtils::PassRingCutNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  return GetNRecoRingNumuCCQE(event) == 1;

}

// ********************************************************
bool SelectionUtils::PassSubeventCutNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  return event.reco_nsubeve == 1 || event.reco_nsubeve == 2;

}

// ********************************************************
bool SelectionUtils::PassFVCutNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  double towall = GeomUtils::CalcToWallDis(
                  event.reco_1r_pos[PIDCate::kMuon],event.reco_1r_dir[PIDCate::kMuon]);
  double dwall = GeomUtils::CalcDWallDis(event.reco_1r_pos[PIDCate::kMuon]);  

  return towall > 200 && dwall > 100;

}

// ********************************************************
bool SelectionUtils::PassMomCutNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  return event.reco_1r_mom[PIDCate::kMuon] > 200;

}

// ********************************************************
double SelectionUtils::ComputePIDemuRatio(AnafiTQunEvent &event){
// ********************************************************

  if(event.reco_1r_nllh.size() < 1) return -1e8;  

  return event.reco_1r_nllh[PIDCate::kMuon] - event.reco_1r_nllh[PIDCate::kElectron];

}

// ********************************************************
bool SelectionUtils::PassPIDemuCutNumuCCQE(AnafiTQunEvent &event){
// ********************************************************

  return ComputePIDemuRatio(event) < 0;

}