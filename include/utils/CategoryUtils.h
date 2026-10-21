#ifndef CATEGORYUTILS_H
#define CATEGORYUTILS_H

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"
#include "utils/GeomUtils.h"

namespace CategoryUtils{

  // ----------------------------------------
  // PID categories

  enum PIDCate{
    kGamma = 0,
    kElectron,
    kMuon,
    kPion,
    kKaon,
    kProton,
    kRest
  };

  // Get PID category type
  PIDCate GetPIDCateType(AnafiTQunEvent &event);

  // ----------------------------------------
  // Interaction categories

  enum InterCate{
    kNumuCCQE = 0,
    kNumuNonQE,
    kNueCCQE,
    kNueNonQE,
    kNC,
    kOther
  };

  // Get interaction category type
  InterCate GetInterCateType(AnafiTQunEvent &event);

};

#endif