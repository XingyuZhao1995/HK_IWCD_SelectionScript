#include "base/BasefiTQunAnalysis.h"

// -------- Public member functions --------

// ********************************************************
void BasefiTQunAnalysis::RunAnalysis(){
// ********************************************************

  // Overall initialization
  OverallInitialization();

  // Loop over input files and run the analysis
  RunInputFileLoop();

  // Save output file
  SaveOutputFile();

}

// -------- Private member functions --------

// ********************************************************
void BasefiTQunAnalysis::RunInputFileLoop(){
// ********************************************************

  // Some auxiliary variables
  std::string fin_name;
  std::string line;
  std::string suffix = ".root"; // Input file is ROOT

  // Check whether the provided path exists before using it
  if(!std::filesystem::exists(fin_list_name)){
    std::cerr << "ERROR: input path does not exist: " << fin_list_name << std::endl;
    return;
  }

  // Input is a single file
  if(fin_list_name.size() >= suffix.size() &&
     fin_list_name.compare(fin_list_name.size() - suffix.size(),suffix.size(),suffix) == 0){
    std::cout << "----> Now processing file " << fin_list_name << " ..." << std::endl;
    // Run analysis on the single file
    RunSingleFile(fin_list_name);
    return;
  }

  // Else, input is a list
  std::ifstream fin_list(fin_list_name);
  std::cout << "----> Input file list: " << fin_list_name << std::endl;

  // Read input file line by line
  while(std::getline(fin_list,line)){

    std::cout << "----> Now processing file " << line << " ..." << std::endl;

    // Update file name, this is used to fill output tree
    fin_name = line;

    // Check that the referenced file exists
    if(!std::filesystem::exists(fin_name)){
      std::cerr << "ERROR: listed input file does not exist: " << fin_name << std::endl;
      continue;
    }

    // Input file path should end with desired suffix
    if(fin_name.size() >= suffix.size() &&
       fin_name.compare(fin_name.size() - suffix.size(),suffix.size(),suffix) == 0){
      // Run analysis on the single file
      RunSingleFile(fin_name);
    }

  } // End of line loop
  std::cout << "----> All input files processed" << std::endl;

}

// ********************************************************
void BasefiTQunAnalysis::RunSingleFile(std::string file_name){
// ********************************************************

  // ---------------------------------------
  // Read input file and trees
  // ---------------------------------------

  // Open the input file and tree
  TFile *fin = new TFile(file_name.data(),"read");
  if(!fin){
    std::cout << "ERROR: can't open file "<< file_name << std::endl;
    return;
  }

  // (NEUT RooTracker tree)
  TTree *tin_NRooTrk = (TTree*)fin->Get("fRooTrackerOutputTree");
  if(!tin_NRooTrk){
    std::cout << "ERROR: tree fRooTrackerOutputTree not exist" << std::endl;
    return;    
  }

  // (fiTQun tree)
  TTree *tin_fiTQun = (TTree*)fin->Get("fiTQun");
  if(!tin_fiTQun){
    std::cout << "ERROR: tree fiTQun not exist" << std::endl;
    return;    
  }

  if(tin_NRooTrk->GetEntries() != tin_fiTQun->GetEntries()){
    std::cout << "ERROR: fRooTrackerOutputTree and fiTQun do not have same number of entries" << std::endl;
    return;
  }

  // ---------------------------------------
  // Link tree branches
  // ---------------------------------------  

  // NEUT RooTracker tree
  tin_NRooTrk->SetBranchAddress("NRooTrackerVtx",&NRooTrackerVtx);

  // fiTQun tree
  tin_fiTQun->SetBranchAddress("cluster_ncand",&cluster_ncand);
  tin_fiTQun->SetBranchAddress("cluster_tstart",&cluster_tstart);
  tin_fiTQun->SetBranchAddress("cluster_tend",&cluster_tend);
  tin_fiTQun->SetBranchAddress("cluster_nhits",&cluster_nhits);
  tin_fiTQun->SetBranchAddress("cluster_totq",&cluster_totq);  

  tin_fiTQun->SetBranchAddress("fqntwnd",&fqntwnd);
  tin_fiTQun->SetBranchAddress("fqtwnd_iclstr",&fqtwnd_iclstr);
  tin_fiTQun->SetBranchAddress("fqtwnd_npeak",&fqtwnd_npeak);
  tin_fiTQun->SetBranchAddress("fqtwnd",&fqtwnd);

  tin_fiTQun->SetBranchAddress("fqnse",&fqnse);
  tin_fiTQun->SetBranchAddress("fqnhitpmt",&fqnhitpmt);
  tin_fiTQun->SetBranchAddress("fqtotq",&fqtotq);

  tin_fiTQun->SetBranchAddress("fq1rpcflg",&fq1rpcflg);
  tin_fiTQun->SetBranchAddress("fq1rmom",&fq1rmom);
  tin_fiTQun->SetBranchAddress("fq1rnll",&fq1rnll);
  tin_fiTQun->SetBranchAddress("fq1rpos",&fq1rpos);
  tin_fiTQun->SetBranchAddress("fq1rdir",&fq1rdir);

  tin_fiTQun->SetBranchAddress("fqnmrfit",&fqnmrfit);
  tin_fiTQun->SetBranchAddress("fqmrifit",&fqmrifit);
  tin_fiTQun->SetBranchAddress("fqmrnring",&fqmrnring);
  tin_fiTQun->SetBranchAddress("fqmrpcflg",&fqmrpcflg);
  tin_fiTQun->SetBranchAddress("fqmrnll",&fqmrnll);

  tin_fiTQun->SetBranchAddress("fqpi0pcflg",&fqpi0pcflg);

  tin_fiTQun->SetBranchAddress("muechk_ncand",&muechk_ncand);

  // ---------------------------------------
  // Event loop
  // ---------------------------------------

  // Start event loop
  int n_entry = tin_fiTQun->GetEntries();
  for(int n = 0; n < n_entry; n++){

    tin_NRooTrk->GetEntry(n);
    tin_fiTQun->GetEntry(n);

    // ---------------------------------------
    // Fill event
    // ---------------------------------------

    AnafiTQunEvent event;    

    // NEUT RooTracker tree
    ND::NRooTrackerVtx *NRooTracker_event = (ND::NRooTrackerVtx*)NRooTrackerVtx->At(0);
    event.nrootrackervtx = NRooTracker_event;

    // (Fill vertex information)
    FillInfoUtils::FillNEUTRooTrkVtxInfo(event);

    // fiTQun tree
    int max_index = -1;
    double max_charge = 0;
    for(int i = 0; i < fqnse; i++){
      if(fqtotq[i] > max_charge){
        max_charge = fqtotq[i];
        max_index = i;
      }
    }
    if(max_index < 0) event.reco_tag = false;

    // (Fill reco information)
    if(event.reco_tag){
    
      // Subevent
      event.reco_nsubeve = fqnse;

      // Max subevent
      // (Single ring)
      for(int i = 0; i < NPIDHYPO; i++){
        event.reco_1r_flag.push_back(fq1rpcflg[max_index][i]);
        event.reco_1r_mom.push_back(fq1rmom[max_index][i]);
        event.reco_1r_nllh.push_back(fq1rnll[max_index][i]);

        TVector3 pos_tmp(fq1rpos[max_index][i][0],fq1rpos[max_index][i][1],fq1rpos[max_index][i][2]);
        event.reco_1r_pos.push_back(pos_tmp);

        TVector3 dir_tmp(fq1rdir[max_index][i][0],fq1rdir[max_index][i][1],fq1rdir[max_index][i][2]);
        if(dir_tmp.Mag() > 0) dir_tmp *= (1.0 / dir_tmp.Mag());
        event.reco_1r_dir.push_back(dir_tmp);
      }

      // (Multi ring)
      event.reco_mr_nfit = 0;
      for(int i = 0; i < fqnmrfit; i++){
        if(fqmrpcflg[i] != 0) continue;

        event.reco_mr_nfit += 1;
        event.reco_mr_ifit.push_back(fqmrifit[i]);
        event.reco_mr_nring.push_back(fqmrnring[i]);
        event.reco_mr_nllh.push_back(fqmrnll[i]);
      }

    }

    // ---------------------------------------
    // Analyze event
    // ---------------------------------------

    // Run event analysis (implemented in inherited classes)
    RunEventAnalysis(event);

  } // End of event loop

  delete fin;

}