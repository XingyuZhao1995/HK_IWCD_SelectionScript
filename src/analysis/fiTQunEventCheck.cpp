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

  delete fout;

}

// ********************************************************
void fiTQunEventCheck::OverallInitialization(){
// ********************************************************

  // Create output file
  fout = new TFile(fout_name.data(),"recreate");

  // Create output tree
  // (Attach it to the output file so full baskets are flushed to disk instead of kept in memory)
  tout.SetNameTitle("events","events");
  tout.SetDirectory(fout);

  // Create output tree branches
  tout.Branch("cate_type",&cate_type,"cate_type/I");
  tout.Branch("sig_index",&sig_index,"sig_index/I");

  tout.Branch("vtx_pos_true",&vtx_pos_true,"vtx_pos_true[3]/D");
  tout.Branch("vtx_pos_reco",&vtx_pos_reco,"vtx_pos_reco[3]/D");

  tout.Branch("trk_npri_lep",&trk_npri_lep,"trk_npri_lep/I");
  tout.Branch("trk_npri_lep_thres",&trk_npri_lep_thres,"trk_npri_lep_thres/I");
  tout.Branch("trk_npri_p",&trk_npri_p,"trk_npri_p/I");
  tout.Branch("trk_npri_n",&trk_npri_n,"trk_npri_n/I");
  tout.Branch("trk_npri_piplus",&trk_npri_piplus,"trk_npri_piplus/I");
  tout.Branch("trk_npri_piplus_thres",&trk_npri_piplus_thres,"trk_npri_piplus_thres/I");
  tout.Branch("trk_npri_piminus",&trk_npri_piminus,"trk_npri_piminus/I");
  tout.Branch("trk_npri_piminus_thres",&trk_npri_piminus_thres,"trk_npri_piminus_thres/I");
  tout.Branch("trk_npri_pi0",&trk_npri_pi0,"trk_npri_pi0/I");
  tout.Branch("trk_npri_other",&trk_npri_other,"trk_npri_other/I");

  tout.Branch("OD_nhit",&OD_nhit,"OD_nhit/I");
  tout.Branch("OD_charge_tot",&OD_charge_tot,"OD_charge_tot/D");

  tout.Branch("lep_mom_true",&lep_mom_true,"lep_mom_true/D");
  tout.Branch("lep_mom_reco",&lep_mom_reco,"lep_mom_reco/D");
  tout.Branch("lep_mom_reco_hypo",&lep_mom_reco_hypo,"lep_mom_reco_hypo[2]/D");
  tout.Branch("lep_dir_true",&lep_dir_true,"lep_dir_true[3]/D");
  tout.Branch("lep_dir_reco",&lep_dir_reco,"lep_dir_reco[3]/D");
  tout.Branch("lep_PID_emu_reco",&lep_PID_emu_reco,"lep_PID_emu_reco/D");

  tout.Branch("towall_true",&towall_true,"towall_true/D");
  tout.Branch("towall_reco",&towall_reco,"towall_reco/D");
  tout.Branch("dwall_true",&dwall_true,"dwall_true/D");
  tout.Branch("dwall_reco",&dwall_reco,"dwall_reco/D");

  tout.Branch("nsubeve_reco",&nsubeve_reco,"nsubeve_reco/I");
  tout.Branch("subeve_max_index",&subeve_max_index,"subeve_max_index/I");
  tout.Branch("subeve_max_PDG",&subeve_max_PDG);
  tout.Branch("subeve_max_pri",&subeve_max_pri);

  tout.Branch("nring_reco",&nring_reco,"nring_reco/I");
  tout.Branch("nllh_1ring_reco",&nllh_1ring_reco,"nllh_1ring_reco/D");
  tout.Branch("nllh_2ring_reco",&nllh_2ring_reco,"nllh_2ring_reco/D");
  tout.Branch("nllh_3ring_reco",&nllh_3ring_reco,"nllh_3ring_reco/D");

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
  tout.Write();
  // Detach before closing, otherwise TFile::Close() would delete this member tree
  tout.SetDirectory(nullptr);
  fout->Close();

}

// -------- Private member functions --------

// ********************************************************
bool fiTQunEventCheck::ApplyEventCut(AnafiTQunEvent &event){
// ********************************************************

  // Should have true NEUT vertex
  if(!event.nrootrackervtx) return false;

  // Should have reconstruction result
  if(!event.reco_tag) return false;

  return true;

}

// ********************************************************
void fiTQunEventCheck::FillOutputTree(AnafiTQunEvent &event){
// ********************************************************

  subeve_max_PDG.clear();
  subeve_max_pri.clear();

  // Event category
  cate_type = event.cate_type;
  if(SelectionUtils::IsTrueNumuCCQESignal(event)) sig_index = 0;
  else if(SelectionUtils::IsTrueNueCCQESignal(event)) sig_index = 1;
  else sig_index = -1;

  // Vertex information
  vtx_pos_true[0] = event.nu_vtx_pos.X();
  vtx_pos_true[1] = event.nu_vtx_pos.Y();
  vtx_pos_true[2] = event.nu_vtx_pos.Z();

  CategoryUtils::PIDCate par_index = CategoryUtils::GetPIDCateType(event);
  vtx_pos_reco[0] = event.reco_1r_pos[par_index].X();
  vtx_pos_reco[1] = event.reco_1r_pos[par_index].Y();
  vtx_pos_reco[2] = event.reco_1r_pos[par_index].Z();

  // Track information
  trk_npri_lep = event.trk_npri_lep;
  trk_npri_lep_thres = event.trk_npri_lep_thres;
  trk_npri_p = event.trk_npri_p;
  trk_npri_n = event.trk_npri_n;
  trk_npri_piplus = event.trk_npri_piplus;
  trk_npri_piplus_thres = event.trk_npri_piplus_thres;
  trk_npri_piminus = event.trk_npri_piminus;
  trk_npri_piminus_thres = event.trk_npri_piminus_thres;
  trk_npri_pi0 = event.trk_npri_pi0;
  trk_npri_other = event.trk_npri_other;

  // OD information
  OD_nhit = event.OD_nhit;
  OD_charge_tot = event.OD_charge_tot;

  // Lepton information
  lep_mom_true = event.trk_pri_lep_mom;
  lep_mom_reco = event.reco_1r_mom[par_index];
  lep_mom_reco_hypo[0] = event.reco_1r_mom[PIDCate::kElectron];
  lep_mom_reco_hypo[1] = event.reco_1r_mom[PIDCate::kMuon];

  lep_dir_true[0] = event.trk_pri_lep_dir.X();
  lep_dir_true[1] = event.trk_pri_lep_dir.Y();
  lep_dir_true[2] = event.trk_pri_lep_dir.Z();

  lep_dir_reco[0] = event.reco_1r_dir[par_index].X();
  lep_dir_reco[1] = event.reco_1r_dir[par_index].Y();
  lep_dir_reco[2] = event.reco_1r_dir[par_index].Z();

  lep_PID_emu_reco = SelectionUtils::ComputePIDemuRatio(event);

  // Geometry information
  towall_true = event.trk_pri_lep_towall;
  towall_reco = GeomUtils::CalcToWallDis(
                event.reco_1r_pos[par_index],event.reco_1r_dir[par_index]);
  dwall_true = event.trk_pri_lep_dwall;
  dwall_reco = GeomUtils::CalcDWallDis(event.reco_1r_pos[par_index]);

  // Subevent information
  nsubeve_reco = event.reco_nsubeve;
  subeve_max_index = event.reco_subeve_max_index;
  subeve_max_PDG = event.reco_subeve_max_PDG;
  subeve_max_pri = event.reco_subeve_max_pri;

  // Ring counting information
  nring_reco = SelectionUtils::GetNRecoRing(event,par_index);
  nllh_1ring_reco = SelectionUtils::GetMinNegLLH1Ring(event,par_index);
  nllh_2ring_reco = SelectionUtils::GetMinNegLLH2Ring(event);
  nllh_3ring_reco = SelectionUtils::GetMinNegLLH3Ring(event);

  tout.Fill();

}