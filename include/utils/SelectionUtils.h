#ifndef SELECTIONUTILS_H
#define SELECTIONUTILS_H

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"
#include "utils/CategoryUtils.h"

using namespace CategoryUtils;

namespace SelectionUtils{

  // ----------------------------------------
  // PID cut

  // Compute PID likelihood ratio
  double ComputePIDemuRatio(AnafiTQunEvent &event);

};

#endif