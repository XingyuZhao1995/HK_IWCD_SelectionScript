#ifndef FITQUNEVENTCHECK_H
#define FITQUNEVENTCHECK_H

#include "base/BasefiTQunAnalysis.h"

// Analysis class
class fiTQunEventCheck : public BasefiTQunAnalysis{

public:

  // Constructor
  fiTQunEventCheck(std::string in_list_name, std::string out_name);
  // Destructor
  ~fiTQunEventCheck();

  // ----------------------------------------------
  // Actual implementations

  // Overall initialization
  void OverallInitialization();
  
  // Run event analysis 
  void RunEventAnalysis(AnafiTQunEvent &event);  

  // Save output file 
  void SaveOutputFile();

private:

  // Output file name
  std::string fout_name;  

  // Output file
  TFile *fout;

  // Output tree
  TTree *tout;

  // ----------------------------------------------
  // Output tree branch variables

  


};

#endif