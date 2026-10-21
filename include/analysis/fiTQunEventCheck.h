#ifndef FITQUNEVENTCHECK_H
#define FITQUNEVENTCHECK_H

#include "base/BasefiTQunAnalysis.h"
#include "utils/CategoryUtils.h"
#include "utils/SelectionUtils.h"
#include "utils/GeomUtils.h"

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
  // Auxiliary functions

  // Fill output tree
  void FillOutputTree(AnafiTQunEvent &event);

  // ----------------------------------------------
  // Output tree branch variables

  int cate_type;

  double vtx_pos_true[3];
  double vtx_pos_reco[3];

  double lep_mom_true;
  double lep_mom_reco;
  double lep_dir_true[3];
  double lep_dir_reco[3];
  double lep_PID_emu_reco;

  double towall_true;
  double towall_reco;
  double dwall_true;
  double dwall_reco;

  int nsubeve_reco;
  int nring_reco;
  double nllh_1ring_reco;
  double nllh_2ring_reco;
  double nllh_3ring_reco;

};

#endif