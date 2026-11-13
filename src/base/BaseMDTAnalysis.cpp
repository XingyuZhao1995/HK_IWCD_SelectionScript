#include "base/BaseMDTAnalysis.h"

// -------- Public member functions --------

// ********************************************************
BaseMDTAnalysis::BaseMDTAnalysis(std::string in_list_name){
// ********************************************************

  fin_list_name = in_list_name;
    
  // Branch objects are owned by this class and reused for every input file
  WCSim_ID_event = new WCSimRootEvent();
  WCSim_OD_event = new WCSimRootEvent();

}

// ********************************************************
BaseMDTAnalysis::~BaseMDTAnalysis(){
// ********************************************************

  delete WCSim_ID_event;
  delete WCSim_OD_event;

}

// ********************************************************
void BaseMDTAnalysis::RunAnalysis(){
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
void BaseMDTAnalysis::RunInputFileLoop(){
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
      return;
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
void BaseMDTAnalysis::RunSingleFile(std::string file_name){
// ********************************************************

  // ---------------------------------------
  // Read input file and trees
  // ---------------------------------------

  // Open the MDT file and tree
  std::unique_ptr<TFile> fin_MDT(TFile::Open(file_name.data(),"read"));
  if(!fin_MDT || fin_MDT->IsZombie()){
    std::cout << "ERROR: can't open file "<< file_name << std::endl;
    return;
  }

  // (WCSim-like tree)
  TTree *tin_MDT = (TTree*)fin_MDT->Get("wcsimT");
  if(!tin_MDT){
    std::cout << "ERROR: tree wcsimT not exist" << std::endl;
    return;    
  }   

  // (Pile-up info tree)
  TTree *tin_pileup = (TTree*)fin_MDT->Get("pupspillT");
  if(!tin_pileup){
    std::cout << "ERROR: tree pupspillT not exist" << std::endl;
    return;    
  }   

  // Tree entries check
  if(tin_MDT->GetEntries() != tin_pileup->GetEntries()){
    std::cout << "ERROR: wcsimT and pupspillT do not have same number of entries" << std::endl;
    return;
  } 

  // ---------------------------------------
  // Link tree branches
  // ---------------------------------------  

  // WCSim-like tree
  tin_MDT->SetBranchAddress("wcsimrootevent",&WCSim_ID_event);
  tin_MDT->SetBranchAddress("wcsimrootevent_OD",&WCSim_OD_event);  

  // Pile-up info tree
  tin_pileup->SetBranchAddress("NNuIntTot",&NNuIntTot);
  tin_pileup->SetBranchAddress("FileIdNum",&FileIdNum);
  tin_pileup->SetBranchAddress("EventIdNum",&EventIdNum);
  tin_pileup->SetBranchAddress("NIDNuInt",&NIDNuInt);
  tin_pileup->SetBranchAddress("NBeamBkg",&NBeamBkg);
  tin_pileup->SetBranchAddress("NeutCode",&NeutCode);
  tin_pileup->SetBranchAddress("NuDir",&NuDir);
  tin_pileup->SetBranchAddress("NuEne",&NuEne);
  tin_pileup->SetBranchAddress("NuIntBunch",&NuIntBunch);
  tin_pileup->SetBranchAddress("NuIntTime",&NuIntTime);
  tin_pileup->SetBranchAddress("NuPDG",&NuPDG);
  tin_pileup->SetBranchAddress("NuPos",&NuPos);

  tin_pileup->SetBranchAddress("NTracks",&NTracks);
  tin_pileup->SetBranchAddress("TrackNuIntIdx",&TrackNuIntIdx);

  tin_pileup->SetBranchAddress("PENuIntIdx",&PENuIntIdx);
  tin_pileup->SetBranchAddress("PENuIntIdx_OD",&PENuIntIdx_OD);

  // ---------------------------------------
  // File level analysis
  // ---------------------------------------

  // Extract run and subrun numbers
  int run, subrun;
  MiscUtils::ReadRunNumberFromFileName(file_name,run,subrun);

  // ---------------------------------------
  // Event loop
  // ---------------------------------------

  // Start event loop
  int n_entry = tin_MDT->GetEntries();
  for(int n = 0; n < n_entry; n++){

    tin_MDT->GetEntry(n);
    tin_pileup->GetEntry(n);

    WCSim_ID_trigger = (WCSimRootTrigger*)WCSim_ID_event->fEventList->At(0);
    WCSim_OD_trigger = (WCSimRootTrigger*)WCSim_OD_event->fEventList->At(0);

    // ---------------------------------------
    // Fill event
    // ---------------------------------------

    AnaMDTEvent event;
    event.run = run;
    event.subrun = subrun;
    event.event_id = WCSim_ID_trigger->fEvtHdr.fEvtNum;

    event.wcsim_ID_event = WCSim_ID_trigger;
    event.wcsim_OD_event = WCSim_OD_trigger;

    // (Fill pile-up information)
    event.n_int = NNuIntTot;
    
    // (Fill interaction information)
    for(int i = 0; i < NNuIntTot; i++){

      event.vec_nu_pdg.push_back(NuPDG[i]);
      event.vec_nu_energy.push_back(NuEne[i]);
      event.vec_nu_neut_code.push_back(NeutCode[i]);

      TVector3 pos_tmp(NuPos[i][0],NuPos[i][1],NuPos[i][2]);
      event.vec_nu_pos.push_back(pos_tmp);

      event.vec_nu_bunch_idx.push_back(NuIntBunch[i]);
      event.vec_nu_time.push_back(NuIntTime[i]);

    } // End of interaction loop

    // (Fill track information)
    event.n_trk = NTracks;
    event.trk_int_idx = TrackNuIntIdx;
    FillInfoUtils::FillMDTG4TrkInfo(event);

    std::cout << "NTracks = " << NTracks
              << ", fNtrack = " << event.wcsim_ID_event->fNtrack
              << std::endl;

    // (Fill true hit information)
    event.vec_pe_int_idx = PENuIntIdx;
    event.vec_pe_OD_int_idx = PENuIntIdx_OD;

    // ---------------------------------------
    // Analyze event
    // ---------------------------------------

    // Run event analysis (implemented in inherited classes)
    RunEventAnalysis(event);

  }  // End of event loop

}