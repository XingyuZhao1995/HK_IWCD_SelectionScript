#include "base/BasefiTQunAnalysis.h"

// -------- Public member functions --------

// ********************************************************
BasefiTQunAnalysis::BasefiTQunAnalysis(std::string in_list_name){
// ********************************************************

  fin_list_name = in_list_name;
    
  // Branch objects are owned by this class and reused for every input file
  WCSim_geom = new WCSimRootGeom();

  WCSim_ID_event = new WCSimRootEvent();
  WCSim_OD_event = new WCSimRootEvent();

  NRooTrackerVtx = new ND::NRooTrackerVtx();

}

// ********************************************************
BasefiTQunAnalysis::~BasefiTQunAnalysis(){
// ********************************************************

  delete WCSim_geom;

  delete WCSim_ID_event;
  delete WCSim_OD_event;

  delete NRooTrackerVtx;

}

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
  std::string fin_WCSim_name, fin_fiTQun_name;
  std::string line;
  std::string suffix = ".root"; // Input file is ROOT

  // Check whether the provided path exists before using it
  if(!std::filesystem::exists(fin_list_name)){
    std::cerr << "ERROR: input path does not exist: " << fin_list_name << std::endl;
    return;
  }

  std::ifstream fin_list(fin_list_name);
  std::cout << "----> Input file list: " << fin_list_name << std::endl;

  // Read input file line by line
  while(std::getline(fin_list,line)){

    std::istringstream iss(line);
    if(!(iss >> fin_WCSim_name >> fin_fiTQun_name)){
      std::cerr << "ERROR: expected two files on line: " << line << std::endl;
      continue;
    }
  
    std::cout << "----> Now processing file " << fin_WCSim_name 
              << " and " << fin_fiTQun_name << " ..." << std::endl;

    // Check that both files exist and end with desired suffix
    bool files_ok = true;
    for(const std::string& name : {fin_WCSim_name, fin_fiTQun_name}){
      if(!std::filesystem::exists(name)){
        std::cerr << "ERROR: listed input file does not exist: " << name << std::endl;
        files_ok = false;
      } 
      if(name.size() < suffix.size() ||
         name.compare(name.size() - suffix.size(),suffix.size(),suffix) != 0){
        std::cerr << "ERROR: listed input file is not ROOT file: " << name << std::endl;
        files_ok = false;
      }     
    }
    if(!files_ok) continue;

    // Run analysis
    RunSingleFile(fin_WCSim_name,fin_fiTQun_name);

  } // End of line loop
  std::cout << "----> All input files processed" << std::endl;

}

// ********************************************************
void BasefiTQunAnalysis::RunSingleFile(std::string file_WCSim_name, std::string file_fiTQun_name){
// ********************************************************

  // ---------------------------------------
  // Read input file and trees
  // ---------------------------------------

  // Open the WCSim file and tree
  std::unique_ptr<TFile> fin_WCSim(TFile::Open(file_WCSim_name.data(),"read"));
  if(!fin_WCSim || fin_WCSim->IsZombie()){
    std::cout << "ERROR: can't open file "<< file_WCSim_name << std::endl;
    return;
  }

  // (Geometry setting)
  TTree *tin_geom = (TTree*)fin_WCSim->Get("wcsimGeoT");
  if(!tin_geom){
    std::cout << "ERROR: tree wcsimGeoT not exist" << std::endl;
    return;    
  }  
  
  // (WCSim tree)
  TTree *tin_WCSim = (TTree*)fin_WCSim->Get("wcsimT");
  if(!tin_WCSim){
    std::cout << "ERROR: tree wcsimT not exist" << std::endl;
    return;    
  }    

  // Open the fiTQun file and tree
  std::unique_ptr<TFile> fin_fiTQun(TFile::Open(file_fiTQun_name.data(),"read"));
  if(!fin_fiTQun || fin_fiTQun->IsZombie()){
    std::cout << "ERROR: can't open file "<< file_fiTQun_name << std::endl;
    return;
  }

  // (NEUT RooTracker tree)
  TTree *tin_NRooTrk = (TTree*)fin_fiTQun->Get("fRooTrackerOutputTree");
  if(!tin_NRooTrk){
    std::cout << "ERROR: tree fRooTrackerOutputTree not exist" << std::endl;
    return;    
  }

  // (fiTQun tree)
  TTree *tin_fiTQun = (TTree*)fin_fiTQun->Get("fiTQun");
  if(!tin_fiTQun){
    std::cout << "ERROR: tree fiTQun not exist" << std::endl;
    return;    
  }

  // Tree entries check
  if(tin_WCSim->GetEntries() != tin_fiTQun->GetEntries()){
    std::cout << "ERROR: WCSim and fiTQun do not have same number of entries" << std::endl;
    return;
  }  
  if(tin_NRooTrk->GetEntries() != tin_fiTQun->GetEntries()){
    std::cout << "ERROR: fRooTrackerOutputTree and fiTQun do not have same number of entries" << std::endl;
    return;
  }

  // ---------------------------------------
  // Link tree branches
  // ---------------------------------------  

  // WCsim file
  // (Geometry tree)
  tin_geom->SetBranchAddress("wcsimrootgeom",&WCSim_geom);

  // (WCSim tree)
  tin_WCSim->SetBranchAddress("wcsimrootevent",&WCSim_ID_event);
  tin_WCSim->SetBranchAddress("wcsimrootevent_OD",&WCSim_OD_event);

  // fiTQun file
  // (NEUT RooTracker tree)
  tin_NRooTrk->SetBranchAddress("NRooTrackerVtx",&NRooTrackerVtx);

  // (fiTQun tree)
  tin_fiTQun->SetBranchAddress("nevt",&nevt);

  tin_fiTQun->SetBranchAddress("cluster_ncand",&cluster_ncand);
  tin_fiTQun->SetBranchAddress("cluster_tstart",&cluster_tstart);
  tin_fiTQun->SetBranchAddress("cluster_tend",&cluster_tend);
  tin_fiTQun->SetBranchAddress("cluster_nhits",&cluster_nhits);
  tin_fiTQun->SetBranchAddress("cluster_totq",&cluster_totq);  

  tin_fiTQun->SetBranchAddress("fqntwnd",&fqntwnd);
  tin_fiTQun->SetBranchAddress("fqtwnd_iclstr",&fqtwnd_iclstr);
  tin_fiTQun->SetBranchAddress("fqtwnd_npeak",&fqtwnd_npeak);
  tin_fiTQun->SetBranchAddress("fqtwnd",&fqtwnd);
  tin_fiTQun->SetBranchAddress("fqtwnd_peakt0",&fqtwnd_peakt0);

  tin_fiTQun->SetBranchAddress("fqnse",&fqnse);
  tin_fiTQun->SetBranchAddress("fqnhitpmt",&fqnhitpmt);
  tin_fiTQun->SetBranchAddress("fqtotq",&fqtotq);
  tin_fiTQun->SetBranchAddress("fqitwnd",&fqitwnd);
  tin_fiTQun->SetBranchAddress("fqipeak",&fqipeak);

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
  tin_fiTQun->SetBranchAddress("fqpi0nll",&fqpi0nll);

  tin_fiTQun->SetBranchAddress("muechk_ncand",&muechk_ncand);

  // ---------------------------------------
  // Event loop
  // ---------------------------------------

  // Start event loop
  int n_entry = tin_fiTQun->GetEntries();
  for(int n = 0; n < n_entry; n++){

    tin_WCSim->GetEntry(n);
    tin_NRooTrk->GetEntry(n);
    tin_fiTQun->GetEntry(n);

    WCSim_ID_trigger = (WCSimRootTrigger*)WCSim_ID_event->fEventList->At(0);
    WCSim_OD_trigger = (WCSimRootTrigger*)WCSim_OD_event->fEventList->At(0);

    // Examine if WCSim and fiTQun entries correspond to the same event
    if(!IsSameEvent()) continue;

    // ---------------------------------------
    // Fill event
    // ---------------------------------------

    AnafiTQunEvent event;    

    // NEUT RooTracker tree
    event.nrootrackervtx = NRooTrackerVtx;

    // (Fill vertex information)
    FillInfoUtils::FillNEUTRooTrkVtxInfo(event);

    // WCSim tree
    event.wcsim_ID_event = WCSim_ID_trigger;
    event.wcsim_OD_event = WCSim_OD_trigger;

    // (Fill track information)
    FillInfoUtils::FillG4TrkInfo(event);

    // (Fill OD hits information)
    FillInfoUtils::FillODHitsInfo(event);

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
      event.reco_subeve_max_index = max_index;
      for(int i = 0; i < fqnse; i++){
        double peak_t0 = fqtwnd_peakt0[fqitwnd[i]][fqipeak[i]];
        int G4_trk_id = MiscUtils::GetSubeventMaxG4TrkID(peak_t0,event);
        WCSimRootTrack *G4_track = MiscUtils::GetG4TrkByID(G4_trk_id,event);
        if(G4_track){
          event.reco_subeve_max_PDG.push_back(G4_track->fIpnu);
          event.reco_subeve_max_pri.push_back(MiscUtils::GetG4TrkParInterInfo(G4_track));    
        }
        else{
          event.reco_subeve_max_PDG.push_back(0);
          event.reco_subeve_max_pri.push_back(-1);          
        }
      }

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

      // Pi0
      event.reco_pi0_nllh = fqpi0nll[0];

    }

    // ---------------------------------------
    // Analyze event
    // ---------------------------------------

    // Run event analysis (implemented in inherited classes)
    RunEventAnalysis(event);

  } // End of event loop

}

// ********************************************************
bool BasefiTQunAnalysis::IsSameEvent(){
// ********************************************************

  if(WCSim_ID_trigger->fEvtHdr.fEvtNum != (nevt - 1)){
    std::cout << "ERROR: WCSim (" << WCSim_ID_trigger->fEvtHdr.fEvtNum
              << ") and fiTQun (" << nevt - 1
              << ") event number not match" << std::endl;
    return false;
  }

  return true;

}