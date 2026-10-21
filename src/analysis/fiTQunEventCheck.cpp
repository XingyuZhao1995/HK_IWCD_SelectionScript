#include "analysis/fiTQunEventCheck.h"

// -------- Public member functions --------

// ********************************************************
fiTQunEventCheck::fiTQunEventCheck(std::string in_list_name, std::string out_name) :
  BasefiTQunAnalysis(in_list_name){
// ********************************************************

  fout_name = out_name;

}

// ********************************************************
fiTQunEventCheck::~fiTQunEventCheck(){
// ********************************************************

  delete tout;
  delete fout;

}

// ********************************************************
void fiTQunEventCheck::OverallInitialization(){
// ********************************************************

  // Create output file
  fout = new TFile(fout_name.data(),"recreate");

  // Create output tree
  tout = new TTree("events","events");

  // Create output tree branches
  tout->Branch("cate_type",&cate_type,"cate_type/I");

  tout->Branch("vtx_pos_true",&vtx_pos_true,"vtx_pos_true[3]/D");
  tout->Branch("vtx_pos_reco",&vtx_pos_reco,"vtx_pos_reco[3]/D");

  tout->Branch("lep_mom_true",&lep_mom_true,"lep_mom_true/D");
  tout->Branch("lep_mom_reco",&lep_mom_reco,"lep_mom_reco/D");
  tout->Branch("lep_dir_true",&lep_dir_true,"lep_dir_true[3]/D");
  tout->Branch("lep_dir_reco",&lep_dir_reco,"lep_dir_reco[3]/D");
  tout->Branch("lep_PID_emu_reco",&lep_PID_emu_reco,"lep_PID_emu_reco/D");

  tout->Branch("towall_true",&towall_true,"towall_true/D");
  tout->Branch("towall_reco",&towall_reco,"towall_reco/D");
  tout->Branch("dwall_true",&dwall_true,"dwall_true/D");
  tout->Branch("dwall_reco",&dwall_reco,"dwall_reco/D");

  tout->Branch("nsubeve_reco",&nsubeve_reco,"nsubeve_reco/I");
  tout->Branch("nring_reco",&nring_reco,"nring_reco/I");
  tout->Branch("nllh_1ring_reco",&nllh_1ring_reco,"nllh_1ring_reco/D");
  tout->Branch("nllh_2ring_reco",&nllh_2ring_reco,"nllh_2ring_reco/D");
  tout->Branch("nllh_3ring_reco",&nllh_3ring_reco,"nllh_3ring_reco/D");

}

// ********************************************************
void fiTQunEventCheck::RunEventAnalysis(AnafiTQunEvent &event){
// ********************************************************

  // Apply event cut
  bool ok = ApplyEventCut(event);
  if(!ok) return;

  // Fill output tree
  FillOutputTree(event);

}

// ********************************************************
void fiTQunEventCheck::SaveOutputFile(){
// ********************************************************

  fout->cd();
  tout->Write();
  fout->Close();

}

// -------- Private member functions --------

// ********************************************************
bool fiTQunEventCheck::ApplyEventCut(AnafiTQunEvent &event){
// ********************************************************

  // Should have reconstruction result
  if(!event.reco_tag) return false;

  return true;

}

// ********************************************************
void fiTQunEventCheck::FillOutputTree(AnafiTQunEvent &event){
// ********************************************************

  // Event category
  cate_type = CategoryUtils::GetInterCateType(event);

  // Vertex information
  vtx_pos_true[0] = event.nu_vtx_pos.X();
  vtx_pos_true[1] = event.nu_vtx_pos.Y();
  vtx_pos_true[2] = event.nu_vtx_pos.Z();

  CategoryUtils::PIDCate par_index = CategoryUtils::GetPIDCateType(event);
  vtx_pos_reco[0] = event.reco_1r_pos[par_index].X();
  vtx_pos_reco[1] = event.reco_1r_pos[par_index].Y();
  vtx_pos_reco[2] = event.reco_1r_pos[par_index].Z();

  // Lepton information
  lep_mom_true = event.nu_pri_lep_mom;
  lep_mom_reco = event.reco_1r_mom[par_index];

  lep_dir_true[0] = event.nu_pri_lep_dir.X();
  lep_dir_true[1] = event.nu_pri_lep_dir.Y();
  lep_dir_true[2] = event.nu_pri_lep_dir.Z();

  lep_dir_reco[0] = event.reco_1r_dir[par_index].X();
  lep_dir_reco[1] = event.reco_1r_dir[par_index].Y();
  lep_dir_reco[2] = event.reco_1r_dir[par_index].Z();

  lep_PID_emu_reco = SelectionUtils::ComputePIDemuRatio(event);

  // Geometry information
  towall_true = GeomUtils::CalcToWallDis(event.nu_vtx_pos,event.nu_pri_lep_dir,true);
  towall_reco = GeomUtils::CalcToWallDis(
                event.reco_1r_pos[par_index],event.reco_1r_dir[par_index]);
  dwall_true = GeomUtils::CalcDWallDis(event.nu_vtx_pos,true);
  dwall_reco = GeomUtils::CalcDWallDis(event.reco_1r_pos[par_index]);

  // Event general information
  nsubeve_reco = event.reco_nsubeve;
  nring_reco = SelectionUtils::GetNRecoRing(event,par_index);
  nllh_1ring_reco = SelectionUtils::GetMinNegLLH1Ring(event,par_index);
  nllh_2ring_reco = SelectionUtils::GetMinNegLLH2Ring(event);
  nllh_3ring_reco = SelectionUtils::GetMinNegLLH3Ring(event);

  tout->Fill();

}