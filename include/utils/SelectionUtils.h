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

  // ----------------------------------------
  // PID cut

  // Compute PID likelihood ratio
  double ComputePIDemuRatio(AnafiTQunEvent &event);

  // ----------------------------------------
  // Ring cut

  // Get minimum negative LLH for each ring hypothesis
  double GetMinNegLLH1Ring(AnafiTQunEvent &event, PIDCate par_type);
  double GetMinNegLLH2Ring(AnafiTQunEvent &event);
  double GetMinNegLLH3Ring(AnafiTQunEvent &event);

  // Get number of reconstructed rings
  int GetNRecoRing(AnafiTQunEvent &event, PIDCate par_type);

};

#endif