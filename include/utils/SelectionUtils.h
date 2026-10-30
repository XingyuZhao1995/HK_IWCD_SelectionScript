#ifndef SELECTIONUTILS_H
#define SELECTIONUTILS_H

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"
#include "utils/CategoryUtils.h"
#include "utils/GeomUtils.h"

using namespace CategoryUtils;

namespace SelectionUtils{

  // ----------------------------------------
  // Signal cut

  // Cut at truth level
  bool IsTrueNumuCCQESignal(AnafiTQunEvent &event);
  bool IsTrueNueCCQESignal(AnafiTQunEvent &event);

  // Get signal index
  int GetSignalIndex(AnafiTQunEvent &event);

  // ----------------------------------------
  // OD cut

  // Apply cut
  bool PassODVetoNumuCCQE(AnafiTQunEvent &event);

  // ----------------------------------------
  // Ring cut

  // Get minimum negative LLH for each ring hypothesis
  double GetMinNegLLH1Ring(AnafiTQunEvent &event, PIDCate par_type);
  double GetMinNegLLH2Ring(AnafiTQunEvent &event);
  double GetMinNegLLH3Ring(AnafiTQunEvent &event);

  // Get number of reconstructed rings
  int GetNRecoRingRef(AnafiTQunEvent &event, PIDCate par_type);
  int GetNRecoRingNumuCCQE(AnafiTQunEvent &event);

  // Apply cut
  bool PassRingCutNumuCCQE(AnafiTQunEvent &event);

  // ----------------------------------------
  // Subevent cut

  // Apply cut
  bool PassSubeventCutNumuCCQE(AnafiTQunEvent &event);

  // ----------------------------------------
  // FV cut

  // Apply cut
  bool PassFVCutNumuCCQE(AnafiTQunEvent &event);

  // ----------------------------------------
  // Momentum cut

  // Apply cut
  bool PassMomCutNumuCCQE(AnafiTQunEvent &event);

  // ----------------------------------------
  // PID cut

  // Compute PID likelihood ratio
  double ComputePIDemuRatio(AnafiTQunEvent &event);

  // Apply cut
  bool PassPIDemuCutNumuCCQE(AnafiTQunEvent &event);

};

#endif