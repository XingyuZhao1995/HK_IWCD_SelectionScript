#include <iostream>
#include <sstream>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TClonesArray.h>

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"

// This script checks the MDT electronics simulation output and compares
// the results with WCSim

template <typename T>
void AddHistogram(T *&h_base, T *h_source, TFile *fin, TString name, TString fin_name){

  h_source = (T*)fin->Get(name);
  if(!h_source){
    std::cout << name << " not found in " << fin_name << std::endl;
    return;
  }
  if(!h_base){
    h_base = (T*)h_source->Clone(name);
    h_base->SetDirectory(nullptr);
  }
  else{
    h_base->Add(h_source);
  }

}

void MergeFiles(std::string fin_list_name, std::string fout_name){

  // Temporary variables
  std::string fin_name;
  std::string line;
  std::string suffix = ".root"; // Input file is ROOT
  int n_file_count = 0;
  TH1D *h_temp_1d;

  // Plots to be saved to the output
  TH1D *h_nhit_ID_MDT = nullptr;
  TH1D *h_nhit_ID_WCSim = nullptr;
  TH1D *h_nhit_OD_MDT = nullptr;
  TH1D *h_nhit_OD_WCSim = nullptr;

  TH1D *h_hitT_ID_MDT = nullptr;
  TH1D *h_hitT_ID_WCSim = nullptr;
  TH1D *h_hitT_OD_MDT = nullptr;
  TH1D *h_hitT_OD_WCSim = nullptr;

  TH1D *h_hitT_red_ID_MDT = nullptr;
  TH1D *h_hitT_red_ID_WCSim = nullptr;
  TH1D *h_hitT_red_OD_MDT = nullptr;
  TH1D *h_hitT_red_OD_WCSim = nullptr;

  TH1D *h_hitQ_ID_MDT = nullptr;
  TH1D *h_hitQ_ID_WCSim = nullptr;
  TH1D *h_hitQ_OD_MDT = nullptr;
  TH1D *h_hitQ_OD_WCSim = nullptr;

  // Create input file list
  std::ifstream fin_list(fin_list_name);
  std::cout << "----> Input file list: " << fin_list_name << std::endl;

  // Read input file line by line
  while(std::getline(fin_list,line)){

    // Update file name
    fin_name = line;

    // Input file path should end with desired suffix
    if(fin_name.size() >= suffix.size() &&
       fin_name.compare(fin_name.size() - suffix.size(),suffix.size(),suffix) == 0){

      // Read input file
      TFile *fin = new TFile(fin_name.data(),"read");

      // Get plots
      AddHistogram(h_nhit_ID_MDT,h_temp_1d,fin,"h_nhit_ID_MDT",fin_name);
      AddHistogram(h_nhit_ID_WCSim,h_temp_1d,fin,"h_nhit_ID_WCSim",fin_name);
      AddHistogram(h_nhit_OD_MDT,h_temp_1d,fin,"h_nhit_OD_MDT",fin_name);
      AddHistogram(h_nhit_OD_WCSim,h_temp_1d,fin,"h_nhit_OD_WCSim",fin_name);

      AddHistogram(h_hitT_ID_MDT,h_temp_1d,fin,"h_hitT_ID_MDT",fin_name);
      AddHistogram(h_hitT_ID_WCSim,h_temp_1d,fin,"h_hitT_ID_WCSim",fin_name);
      AddHistogram(h_hitT_OD_MDT,h_temp_1d,fin,"h_hitT_OD_MDT",fin_name);
      AddHistogram(h_hitT_OD_WCSim,h_temp_1d,fin,"h_hitT_OD_WCSim",fin_name);

      AddHistogram(h_hitT_red_ID_MDT,h_temp_1d,fin,"h_hitT_red_ID_MDT",fin_name);
      AddHistogram(h_hitT_red_ID_WCSim,h_temp_1d,fin,"h_hitT_red_ID_WCSim",fin_name);
      AddHistogram(h_hitT_red_OD_MDT,h_temp_1d,fin,"h_hitT_red_OD_MDT",fin_name);
      AddHistogram(h_hitT_red_OD_WCSim,h_temp_1d,fin,"h_hitT_red_OD_WCSim",fin_name);

      AddHistogram(h_hitQ_ID_MDT,h_temp_1d,fin,"h_hitQ_ID_MDT",fin_name);
      AddHistogram(h_hitQ_ID_WCSim,h_temp_1d,fin,"h_hitQ_ID_WCSim",fin_name);
      AddHistogram(h_hitQ_OD_MDT,h_temp_1d,fin,"h_hitQ_OD_MDT",fin_name);
      AddHistogram(h_hitQ_OD_WCSim,h_temp_1d,fin,"h_hitQ_OD_WCSim",fin_name);      

      // Update file counter
      n_file_count += 1;
      if(n_file_count % 50 == 0){
        std::cout << "----> " << n_file_count << " files counted" << std::endl;
      }

      delete fin;

    }

  } // End of line loop
  std::cout << "----> All input files processed" << std::endl;

  // Create output file
  TFile *fout = new TFile(fout_name.data(),"recreate");
  fout->cd();

  h_nhit_ID_MDT->Write();
  h_nhit_ID_WCSim->Write();
  h_nhit_OD_MDT->Write();
  h_nhit_OD_WCSim->Write();  

  h_hitT_ID_MDT->Write();
  h_hitT_ID_WCSim->Write();
  h_hitT_OD_MDT->Write();
  h_hitT_OD_WCSim->Write();  

  h_hitT_red_ID_MDT->Write();
  h_hitT_red_ID_WCSim->Write();
  h_hitT_red_OD_MDT->Write();
  h_hitT_red_OD_WCSim->Write();    

  h_hitQ_ID_MDT->Write();
  h_hitQ_ID_WCSim->Write();
  h_hitQ_OD_MDT->Write();
  h_hitQ_OD_WCSim->Write();   

  fout->Close();

  delete fout;

}

void RunSingleFile(std::string fin_MDT_name, std::string fin_WCSim_name, std::string fout_name){
  
  // ----------------------------------
  // Read input files
  // ----------------------------------

  // MDT file
  TFile *fin_MDT = new TFile(fin_MDT_name.data(),"read");
  if(!fin_MDT || fin_MDT->IsZombie()){
    std::cout << "ERROR: can't open file "<< fin_MDT_name << std::endl;
    return;
  }

  TTree *tin_MDT = (TTree*)fin_MDT->Get("wcsimT");
  if(!tin_MDT){
    std::cout << "ERROR: tree wcsimT not exist" << std::endl;
    return;    
  }   

  // WCSim file
  TFile *fin_WCSim = new TFile(fin_WCSim_name.data(),"read");
  if(!fin_WCSim || fin_WCSim->IsZombie()){
    std::cout << "ERROR: can't open file "<< fin_WCSim_name << std::endl;
    return;
  }

  TTree *tin_WCSim = (TTree*)fin_WCSim->Get("wcsimT");
  if(!tin_WCSim){
    std::cout << "ERROR: tree wcsimT not exist" << std::endl;
    return;    
  }  

  // Tree branches
  WCSimRootEvent *root_event_MDT_ID = nullptr;
  WCSimRootEvent *root_event_MDT_OD = nullptr;

  WCSimRootEvent *root_event_WCSim_ID = nullptr;
  WCSimRootEvent *root_event_WCSim_OD = nullptr;

  tin_MDT->SetBranchAddress("wcsimrootevent",&root_event_MDT_ID);
  tin_MDT->SetBranchAddress("wcsimrootevent_OD",&root_event_MDT_OD);

  tin_WCSim->SetBranchAddress("wcsimrootevent",&root_event_WCSim_ID);
  tin_WCSim->SetBranchAddress("wcsimrootevent_OD",&root_event_WCSim_OD);

  // ----------------------------------
  // Create plots
  // ----------------------------------  

  // Total hit number distribution
  const int n_bin_hit = 100;
  const double nhit_min = 0;
  const double nhit_max = 3000;

  TH1D h_nhit_ID_MDT;
  h_nhit_ID_MDT.SetNameTitle("h_nhit_ID_MDT","h_nhit_ID_MDT");
  h_nhit_ID_MDT.SetBins(n_bin_hit,nhit_min,nhit_max);
  TH1D h_nhit_ID_WCSim = *((TH1D*)h_nhit_ID_MDT.Clone("h_nhit_ID_WCSim"));

  TH1D h_nhit_OD_MDT;
  h_nhit_OD_MDT.SetNameTitle("h_nhit_OD_MDT","h_nhit_OD_MDT");
  h_nhit_OD_MDT.SetBins(n_bin_hit,nhit_min,nhit_max);
  TH1D h_nhit_OD_WCSim = *((TH1D*)h_nhit_OD_MDT.Clone("h_nhit_OD_WCSim"));  

  // Digi hit time distribution
  const int n_bin_hitT = 100;
  const double hitT_min = 0;
  const double hitT_max = 1e4; // In ns
  const double hitT_red_max = 100;

  TH1D h_hitT_ID_MDT;
  h_hitT_ID_MDT.SetNameTitle("h_hitT_ID_MDT","h_hitT_ID_MDT");
  h_hitT_ID_MDT.SetBins(n_bin_hitT,hitT_min,hitT_max);
  TH1D h_hitT_ID_WCSim = *((TH1D*)h_hitT_ID_MDT.Clone("h_hitT_ID_WCSim"));

  TH1D h_hitT_OD_MDT;
  h_hitT_OD_MDT.SetNameTitle("h_hitT_OD_MDT","h_hitT_OD_MDT");
  h_hitT_OD_MDT.SetBins(n_bin_hitT,hitT_min,hitT_max);
  TH1D h_hitT_OD_WCSim = *((TH1D*)h_hitT_OD_MDT.Clone("h_hitT_OD_WCSim"));

  TH1D h_hitT_red_ID_MDT;
  h_hitT_red_ID_MDT.SetNameTitle("h_hitT_red_ID_MDT","h_hitT_red_ID_MDT");
  h_hitT_red_ID_MDT.SetBins(n_bin_hitT,hitT_min,hitT_red_max);
  TH1D h_hitT_red_ID_WCSim = *((TH1D*)h_hitT_red_ID_MDT.Clone("h_hitT_red_ID_WCSim"));

  TH1D h_hitT_red_OD_MDT;
  h_hitT_red_OD_MDT.SetNameTitle("h_hitT_red_OD_MDT","h_hitT_red_OD_MDT");
  h_hitT_red_OD_MDT.SetBins(n_bin_hitT,hitT_min,hitT_red_max);
  TH1D h_hitT_red_OD_WCSim = *((TH1D*)h_hitT_red_OD_MDT.Clone("h_hitT_red_OD_WCSim"));

  // Digi hit charge distribution
  const int n_bin_hitQ = 100;
  const double hitQ_min = 0;
  const double hitQ_max = 500; // In arbitrary unit (prop. to p.e.)

  TH1D h_hitQ_ID_MDT;
  h_hitQ_ID_MDT.SetNameTitle("h_hitQ_ID_MDT","h_hitQ_ID_MDT");
  h_hitQ_ID_MDT.SetBins(n_bin_hitQ,hitQ_min,hitQ_max);
  TH1D h_hitQ_ID_WCSim = *((TH1D*)h_hitQ_ID_MDT.Clone("h_hitQ_ID_WCSim"));

  TH1D h_hitQ_OD_MDT;
  h_hitQ_OD_MDT.SetNameTitle("h_hitQ_OD_MDT","h_hitQ_OD_MDT");
  h_hitQ_OD_MDT.SetBins(n_bin_hitQ,hitQ_min,hitQ_max);
  TH1D h_hitQ_OD_WCSim = *((TH1D*)h_hitQ_OD_MDT.Clone("h_hitQ_OD_WCSim"));

  // ----------------------------------
  // Event loop
  // ----------------------------------  

  for(int n = 0; n < tin_MDT->GetEntries(); n++){

    tin_MDT->GetEntry(n);
    WCSimRootTrigger *trigger_ID = (WCSimRootTrigger*)root_event_MDT_ID->fEventList->At(0);
    WCSimRootTrigger *trigger_OD = (WCSimRootTrigger*)root_event_MDT_OD->fEventList->At(0);
    if(!trigger_ID || !trigger_OD) continue;

    int n_hit_ID_count = 0;
    int n_hit_OD_count = 0;

    // Loop over ID digitized hits
    for(int i = 0; i < trigger_ID->fNcherenkovdigihits; i++){
      WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)trigger_ID->fCherenkovDigiHits->At(i);
      if(!hit) continue;
      n_hit_ID_count += 1;
      // Fill plots
      h_hitT_ID_MDT.Fill(hit->fT);
      h_hitT_red_ID_MDT.Fill(hit->fT);
      h_hitQ_ID_MDT.Fill(hit->fQ);
    }
    h_nhit_ID_MDT.Fill(n_hit_ID_count);

    // Loop over OD digitized hits
    for(int i = 0; i < trigger_OD->fNcherenkovdigihits; i++){
      WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)trigger_OD->fCherenkovDigiHits->At(i);
      if(!hit) continue;
      n_hit_OD_count += 1;
      // Fill plots
      h_hitT_OD_MDT.Fill(hit->fT);
      h_hitT_red_OD_MDT.Fill(hit->fT);
      h_hitQ_OD_MDT.Fill(hit->fQ);
    }
    h_nhit_OD_MDT.Fill(n_hit_OD_count);

  } // End of event loop

  for(int n = 0; n < tin_WCSim->GetEntries(); n++){

    tin_WCSim->GetEntry(n);
    WCSimRootTrigger *trigger_ID = (WCSimRootTrigger*)root_event_WCSim_ID->fEventList->At(0);
    WCSimRootTrigger *trigger_OD = (WCSimRootTrigger*)root_event_WCSim_OD->fEventList->At(0);
    if(!trigger_ID || !trigger_OD) continue;

    int n_hit_ID_count = 0;
    int n_hit_OD_count = 0;

    // Loop over ID digitized hits
    for(int i = 0; i < trigger_ID->fNcherenkovdigihits; i++){
      WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)trigger_ID->fCherenkovDigiHits->At(i);
      if(!hit) continue;
      n_hit_ID_count += 1;
      // Fill plots
      h_hitT_ID_WCSim.Fill(hit->fT);
      h_hitT_red_ID_WCSim.Fill(hit->fT);
      h_hitQ_ID_WCSim.Fill(hit->fQ);
    }
    h_nhit_ID_WCSim.Fill(n_hit_ID_count);

    // Loop over OD digitized hits
    for(int i = 0; i < trigger_OD->fNcherenkovdigihits; i++){
      WCSimRootCherenkovDigiHit *hit = (WCSimRootCherenkovDigiHit*)trigger_OD->fCherenkovDigiHits->At(i);
      if(!hit) continue;
      n_hit_OD_count += 1;
      // Fill plots
      h_hitT_OD_WCSim.Fill(hit->fT);
      h_hitT_red_OD_WCSim.Fill(hit->fT);
      h_hitQ_OD_WCSim.Fill(hit->fQ);
    }
    h_nhit_OD_WCSim.Fill(n_hit_OD_count);

  } // End of event loop

  // ----------------------------------
  // Save plots
  // ----------------------------------  

  TFile *fout = new TFile(fout_name.data(),"recreate");
  fout->cd();

  h_nhit_ID_MDT.Write();
  h_nhit_ID_WCSim.Write();
  h_nhit_OD_MDT.Write();
  h_nhit_OD_WCSim.Write();  

  h_hitT_ID_MDT.Write();
  h_hitT_ID_WCSim.Write();
  h_hitT_OD_MDT.Write();
  h_hitT_OD_WCSim.Write();  

  h_hitT_red_ID_MDT.Write();
  h_hitT_red_ID_WCSim.Write();
  h_hitT_red_OD_MDT.Write();
  h_hitT_red_OD_WCSim.Write();    

  h_hitQ_ID_MDT.Write();
  h_hitQ_ID_WCSim.Write();
  h_hitQ_OD_MDT.Write();
  h_hitQ_OD_WCSim.Write(); 

  fout->Close();

  delete fin_MDT;
  delete fin_WCSim;
  delete fout;

}

int main(int argc, char **argv){

  if(argc != 4 && argc != 5){
    std::cout << "Should have 4 or 5 executable + arguments!" << std::endl;
    exit(1);
  }  

  // Run option
  int option = std::stoi(argv[1]);

  // Other input arguments
  std::string fin_list_name, fout_name;
  std::string fin_MDT_name, fin_WCSim_name;
  if(option == 1){
    fin_MDT_name = argv[2];
    fin_WCSim_name = argv[3];
    fout_name = argv[4];
  }
  else{
    fin_list_name = argv[2];
    fout_name = argv[3];    
  }

  std::cout << "---------------------------------" << std::endl;
  std::cout << "Start running MDT electroincs sim check" << std::endl;
  std::cout << "---------------------------------" << std::endl;  

  // Merge plots together
  if(option == 1){
    RunSingleFile(fin_MDT_name,fin_WCSim_name,fout_name);
  }
  // Single file check
  else{
    MergeFiles(fin_list_name,fout_name);
  }

  std::cout << "---------------------------------" << std::endl;
  std::cout << "Finish running MDT electroincs sim check" << std::endl;
  std::cout << "---------------------------------" << std::endl;
   
  return 0;

}