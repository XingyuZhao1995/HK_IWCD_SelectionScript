#ifndef NUMUCCQESELECTION_H
#define NUMUCCQESELECTION_H

#include "base/BasefiTQunAnalysis.h"
#include "utils/SelectionUtils.h"
#include "utils/MiscUtils.h"

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
  // Run file analysis
  void RunFileAnalysis(AnaFile &file);

  // Save output file 
  void SaveOutputFile();

private:

  // Output file name
  std::string fout_name;  

  // Output file
  TFile *fout = nullptr;

  // Output tree
  TTree tout_sele;
  TTree tout_true;

  // ----------------------------------------------
  // Auxiliary functions

  // Run signal selection
  bool PassSigFullSelection(AnafiTQunEvent &event);
  bool PassSigSelection_WallRmv(AnafiTQunEvent &event);
  bool PassSigSelection_MomRmv(AnafiTQunEvent &event);

  // Fill output trees
  void FillSelectionTree(AnafiTQunEvent &event); 
  void FillTruthTree(AnafiTQunEvent &event); 

  // ----------------------------------------------
  // Output tree branch variables

  // Common variables shared by both trees
  int nu_neut_code;
  int cate_type;
  int sig_index;

  // Selection tree
  int trk_npri_lep;
  int trk_npri_lep_thres;
  int trk_npri_p;
  int trk_npri_n;
  int trk_npri_piplus;
  int trk_npri_piplus_thres;
  int trk_npri_piminus;
  int trk_npri_piminus_thres;
  int trk_npri_pi0;
  int trk_npri_other;  

  double towall_reco;
  double dwall_reco;

  double nu_energy_reco;
  double nu_energy_true;

  // Truth tree (for signal only)
  int pass_full;
  int pass_wall_rmv;
  int pass_mom_rmv;

  double towall_true;
  double dwall_true;

  double lep_mom_true;

};

#endif