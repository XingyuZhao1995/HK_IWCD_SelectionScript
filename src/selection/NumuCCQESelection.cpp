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

  tout_sele.Branch("towall_reco",&towall_reco,"towall_reco/D");
  tout_sele.Branch("dwall_reco",&dwall_reco,"dwall_reco/D");

  tout_sele.Branch("nu_energy_reco",&nu_energy_reco,"nu_energy_reco/D");
  tout_sele.Branch("nu_energy_true",&nu_energy_true,"nu_energy_true/D");

  // (Truth tree)
  tout_true.Branch("pass_full",&pass_full,"pass_full/I");
  tout_true.Branch("pass_wall_rmv",&pass_wall_rmv,"pass_wall_rmv/I");
  tout_true.Branch("pass_mom_rmv",&pass_mom_rmv,"pass_mom_rmv/I");

  tout_true.Branch("cate_type",&cate_type,"cate_type/I");

  tout_true.Branch("towall_true",&towall_true,"towall_true/D");
  tout_true.Branch("dwall_true",&dwall_true,"dwall_true/D");

  tout_true.Branch("lep_mom_true",&lep_mom_true,"lep_mom_true/D");

}

// ********************************************************
void NumuCCQESelection::RunEventAnalysis(AnafiTQunEvent &event){
// ********************************************************

  // ---------------------------------------
  // Selection tree
  // ---------------------------------------

  // Perform the full selection
  bool pass_full = PassSigFullSelection(event);

  // Perform additional selections
  // Some cuts are removed in these selections
  bool pass_part = PassSigSelection_WallRmv(event);
  pass_part = PassSigSelection_MomRmv(event);

  if(pass_full){
    FillSelectionTree(event);
  }  

  // ---------------------------------------
  // Truth tree
  // ---------------------------------------

  // Check if event should be filled in truth tree
  // Usually only signals are filled
  bool fill_truth = (event.cate_type == 0 && event.trk_pri_lep_stop_ID);
\
  if(fill_truth){
    FillTruthTree(event);
  }

}

// ********************************************************
void NumuCCQESelection::RunFileAnalysis(AnaFile &file){
// ********************************************************

  // Do nothing

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
bool NumuCCQESelection::PassSigFullSelection(AnafiTQunEvent &event){
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
  event.pass_numuCCQE_full = true;
  return true;

}

// ********************************************************
bool NumuCCQESelection::PassSigSelection_WallRmv(AnafiTQunEvent &event){
// ********************************************************

  // Should have reco results
  if(!event.reco_tag) return false;

  // OD veto
  if(!SelectionUtils::PassODVetoNumuCCQE(event)) return false;
  // Number of reconstructed ring cut
  if(!SelectionUtils::PassRingCutNumuCCQE(event)) return false;
  // Number of subevent cut
  if(!SelectionUtils::PassSubeventCutNumuCCQE(event)) return false;
  // Momentum cut
  if(!SelectionUtils::PassMomCutNumuCCQE(event)) return false;
  // e/mu PID cut
  if(!SelectionUtils::PassPIDemuCutNumuCCQE(event)) return false;

  // Mark the event as selection passed
  event.pass_numuCCQE_wall_rmv = true;
  return true;

}

// ********************************************************
bool NumuCCQESelection::PassSigSelection_MomRmv(AnafiTQunEvent &event){
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
  // e/mu PID cut
  if(!SelectionUtils::PassPIDemuCutNumuCCQE(event)) return false;

  // Mark the event as selection passed
  event.pass_numuCCQE_mom_rmv = true;
  return true;

}

// ********************************************************
void NumuCCQESelection::FillSelectionTree(AnafiTQunEvent &event){
// ********************************************************

  cate_type = event.cate_type;

  towall_reco = GeomUtils::CalcToWallDis(
                event.reco_1r_pos[PIDCate::kMuon],event.reco_1r_dir[PIDCate::kMuon]);
  dwall_reco = GeomUtils::CalcDWallDis(event.reco_1r_pos[PIDCate::kMuon]);

  nu_energy_reco = MiscUtils::CalcEnuNumuCCQE(event);
  nu_energy_true = event.nu_energy;
  
  tout_sele.Fill();

}

// ********************************************************
void NumuCCQESelection::FillTruthTree(AnafiTQunEvent &event){
// ********************************************************

  pass_full = event.pass_numuCCQE_full ? 1 : 0;
  pass_wall_rmv = event.pass_numuCCQE_wall_rmv ? 1 : 0;
  pass_wall_rmv = event.pass_numuCCQE_mom_rmv ? 1 : 0;

  cate_type = event.cate_type;

  towall_true = event.trk_pri_lep_towall;
  dwall_true = event.trk_pri_lep_dwall;

  lep_mom_true = event.trk_pri_lep_mom;

  tout_true.Fill();

}