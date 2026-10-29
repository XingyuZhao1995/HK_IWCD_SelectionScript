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
  if(!SelectionUtils::PassODVetoNumuCCQE(event)) return false;
  
  // Number of reconstructed ring cut
  if(!SelectionUtils::PassRingCutNumuCCQE(event)) return false;

  // Number of subevent cut
  if(!SelectionUtils::PassSubeventCutNumuCCQE(event)) return false;

  // FV cut
  if(!SelectionUtils::PassFVCutNumuCCQE(event)) return false;

  // Momentum cut
  if(!SelectionUtils::PassMomCutNumuCCQE(event)) return false;

  // e/mu PID cut
  if(!SelectionUtils::PassPIDemuCutNumuCCQE(event)) return false;

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