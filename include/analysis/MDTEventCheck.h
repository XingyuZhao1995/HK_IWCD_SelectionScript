#ifndef MDTEVENTCHECK_H
#define MDTEVENTCHECK_H

#include "base/BaseMDTAnalysis.h"

// Analysis class
class MDTEventCheck : public BaseMDTAnalysis{

public:

  // Constructor
  MDTEventCheck(std::string in_list_name, std::string out_name);
  // Destructor
  ~MDTEventCheck();

  // ----------------------------------------------
  // Actual implementations

  // Overall initialization
  void OverallInitialization();
  
  // Run event analysis 
  void RunEventAnalysis(AnaMDTEvent &event);  

  // Save output file 
  void SaveOutputFile();

private:

  // Output file name
  std::string fout_name;  

  // Output file
  TFile *fout = nullptr;

  // Output tree
  TTree tout;

  // ----------------------------------------------
  // Auxiliary functions

  // Find bunch index for various pile-up cases
  int FindTwoIntBunchIdx(AnaMDTEvent &event);
  int FindOneMEOneIntBunchIdx(AnaMDTEvent &event);

  // True interaction cut
  bool TrueInteractionCut(AnaMDTEvent &event, int int_index);
  bool PrevMEExistCut(AnaMDTEvent &event, int bunch_index);

  // Fill output tree
  void FillOutputTree(AnaMDTEvent &event, int event_type);

  // ----------------------------------------------
  // Auxiliary variables

  // PMT hit vectors
  std::vector<WCSimRootCherenkovDigiHit*> vec_PMT_hit_ID;
  std::vector<WCSimRootCherenkovDigiHit*> vec_PMT_hit_OD;

  // ----------------------------------------------
  // Output tree branch variables

  int type;

};

#endif