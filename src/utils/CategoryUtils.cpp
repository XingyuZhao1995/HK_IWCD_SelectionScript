#include "utils/CategoryUtils.h"

// ********************************************************
CategoryUtils::PIDCate CategoryUtils::GetPIDCateType(AnafiTQunEvent &event){
// ********************************************************

  if(std::abs(event.nu_pri_lep_pdg) == 11) return PIDCate::kElectron;
  else if(std::abs(event.nu_pri_lep_pdg) == 13) return PIDCate::kMuon;

  return PIDCate::kRest;

}

// ********************************************************
CategoryUtils::InterCate CategoryUtils::GetInterCateType(AnafiTQunEvent &event){
// ********************************************************

  if(!event.nrootrackervtx) return InterCate::kOther;

  // NC
  if(std::abs(event.nu_neut_code) > 30){
    return InterCate::kNC;
  }
  // Numu / Numubar
  else if(std::abs(event.nu_pdg) == 14){
    // CCQE
    if(std::abs(event.nu_neut_code) == 1) return InterCate::kNumuCCQE;
    // Non-QE
    else return InterCate::kNumuNonQE;
  }
  // Nue / nuebar
  else if(std::abs(event.nu_pdg) == 12){
    // CCQE
    if(std::abs(event.nu_neut_code) == 1) return InterCate::kNueCCQE;
    // Non-QE
    else return InterCate::kNueNonQE;
  }

  // Other interactions
  return InterCate::kOther;

}