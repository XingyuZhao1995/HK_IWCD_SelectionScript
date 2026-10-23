#ifndef NUMUCCQESELECTION_H
#define NUMUCCQESELECTION_H

#include "base/BasefiTQunAnalysis.h"
#include "utils/SelectionUtils.h"

// Selection class
class NumuCCQESelection : public BasefiTQunAnalysis{

public:

  // Constructor
  NumuCCQESelection(std::string in_list_name, std::string out_name);
  // Destructor
  ~NumuCCQESelection();

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
  TTree tout_sele;
  TTree tout_true;

  // ----------------------------------------------
  // Auxiliary functions

  // Run signal selection
  bool PassSignalSelection(AnafiTQunEvent &event);

  // Fill output trees
  void FillSelectionTree(AnafiTQunEvent &event); 
  void FillTruthTree(AnafiTQunEvent &event); 

  // ----------------------------------------------
  // Output tree branch variables

  // Common variables shared by both trees
  int cate_type;

  // Selection tree
  

  // Truth tree (for signal only)
  int passed;

};

#endif