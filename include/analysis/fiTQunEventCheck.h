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
  TTree tout;

  // ----------------------------------------------
  // Auxiliary functions

  // Apply event cut
  bool ApplyEventCut(AnafiTQunEvent &event);

  // Fill output tree
  void FillOutputTree(AnafiTQunEvent &event);

  // ----------------------------------------------
  // Output tree branch variables

  int cate_type;
  int sig_index; // 0 = numu CCQE, 1 = nue CCQE, -1 = other

  double vtx_pos_true[3];
  double vtx_pos_reco[3];

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

  int OD_nhit;
  double OD_charge_tot;

  double lep_mom_true;
  double lep_mom_reco;
  double lep_mom_reco_hypo[2]; // 0 = electron, 1 = muon
  double lep_dir_true[3];
  double lep_dir_reco[3];
  double lep_PID_emu_reco;

  double towall_true;
  double towall_reco;
  double dwall_true;
  double dwall_reco;

  int nsubeve_reco;
  int subeve_max_index;
  std::vector<int> subeve_max_PDG;
  std::vector<int> subeve_max_pri;

  int nring_reco;
  double nllh_1ring_reco;
  double nllh_2ring_reco;
  double nllh_3ring_reco;

};

#endif