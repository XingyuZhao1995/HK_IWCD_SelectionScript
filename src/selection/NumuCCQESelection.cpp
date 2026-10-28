#include "selection/NumuCCQESelection.h"

// -------- Public member functions --------

// ********************************************************
NumuCCQESelection::NumuCCQESelection(std::string in_list_name, std::string out_name) :
  BasefiTQunAnalysis(in_list_name){
// ********************************************************

  fout_name = out_name;

}

// ********************************************************
NumuCCQESelection::~NumuCCQESelection(){
// ********************************************************

  delete fout;

}

// ********************************************************
void NumuCCQESelection::OverallInitialization(){
// ********************************************************

  // Create output file
  fout = new TFile(fout_name.data(),"recreate");

  // Create output trees
  // (Attach them to the output file so full baskets are flushed to disk instead of kept in memory)
  tout_sele.SetNameTitle("selection","selection");
  tout_sele.SetDirectory(fout);
  
  tout_true.SetNameTitle("true_signal","true_signal");
  tout_true.SetDirectory(fout);

  // Create output tree branches
  // (Selection tree)
  tout_sele.Branch("cate_type",&cate_type,"cate_type/I");

  // (Truth tree)
  tout_true.Branch("passed",&passed,"passed/I");

  tout_true.Branch("cate_type",&cate_type,"cate_type/I");

}

// ********************************************************
void NumuCCQESelection::RunEventAnalysis(AnafiTQunEvent &event){
// ********************************************************

  // Check if event is true signal
  bool is_signal = SelectionUtils::IsTrueNumuCCQESignal(event);

  // Perform the selection
  bool is_passed = PassSignalSelection(event);

  // Fill output trees
  if(is_passed) FillSelectionTree(event);
  if(is_signal) FillTruthTree(event);

}

// ********************************************************
void NumuCCQESelection::RunFileAnalysis(AnaFile &file){
// ********************************************************



}

// ********************************************************
void NumuCCQESelection::SaveOutputFile(){
// ********************************************************

  fout->cd();
  tout_sele.Write();
  tout_true.Write();
  // Detach before closing, otherwise TFile::Close() would delete these member trees
  tout_sele.SetDirectory(nullptr);
  tout_true.SetDirectory(nullptr);
  fout->Close();

}

// -------- Private member functions --------

// ********************************************************
bool NumuCCQESelection::PassSignalSelection(AnafiTQunEvent &event){
// ********************************************************

  // Should have reco results
  if(!event.reco_tag) return false;

  // OD veto

  
  // Number of reconstructed ring cut
  int n_ring = SelectionUtils::GetNRecoRing(event,PIDCate::kMuon);  
  if(n_ring != 1) return false;

  // Number of subevent cut
  if(!(event.reco_nsubeve == 1 || event.reco_nsubeve == 2)) return false;

  // FV cut
  double towall = GeomUtils::CalcToWallDis(
                  event.reco_1r_pos[PIDCate::kMuon],event.reco_1r_dir[PIDCate::kMuon]);
  double dwall = GeomUtils::CalcDWallDis(event.reco_1r_pos[PIDCate::kMuon]);
  if(!(towall > 200 && dwall > 100)) return false;

  // Momentum cut
  if(event.reco_1r_mom[PIDCate::kMuon] < 200) return false;

  // e/mu PID cut
  double PID_emu = SelectionUtils::ComputePIDemuRatio(event);
  if(PID_emu > 0) return false;

  // Mark the event as selection passed
  event.passed_selection = true;
  return true;

}

// ********************************************************
void NumuCCQESelection::FillSelectionTree(AnafiTQunEvent &event){
// ********************************************************

  cate_type = CategoryUtils::GetInterCateType(event);

  tout_sele.Fill();

}

// ********************************************************
void NumuCCQESelection::FillTruthTree(AnafiTQunEvent &event){
// ********************************************************

  passed = event.passed_selection ? 1 : 0;

  cate_type = CategoryUtils::GetInterCateType(event);

  tout_true.Fill();

}