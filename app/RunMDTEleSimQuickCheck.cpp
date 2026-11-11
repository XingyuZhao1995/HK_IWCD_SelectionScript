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

  tin_MDT->SetBranchAddress("wcsimrootevent",&root_event_WCSim_ID);
  tin_MDT->SetBranchAddress("wcsimrootevent_OD",&root_event_WCSim_OD);

  // ----------------------------------
  // Create plots
  // ----------------------------------  

  // Total hit number distribution
  TH1D h_nhit_ID_MDT;
  h_nhit_ID_MDT.SetNameTitle("h_nhit_ID_MDT","h_nhit_ID_MDT");
  h_nhit_ID_MDT.SetBins(100,0,3000);
  TH1D h_nhit_ID_WCSim = *((TH1D*)h_nhit_ID_MDT.Clone("h_nhit_ID_WCSim"));

  TH1D h_nhit_OD_MDT;
  h_nhit_OD_MDT.SetNameTitle("h_nhit_OD_MDT","h_nhit_OD_MDT");
  h_nhit_OD_MDT.SetBins(100,0,300);
  TH1D h_nhit_OD_WCSim = *((TH1D*)h_nhit_OD_MDT.Clone("h_nhit_OD_WCSim"));  

  // Digi hit time distribution
  TH1D h_hitT_ID_MDT;
  h_hitT_ID_MDT.SetNameTitle("h_hitT_ID_MDT","h_hitT_ID_MDT");
  h_hitT_ID_MDT.SetBins(100,0,10000);
  TH1D h_hitT_ID_WCSim = *((TH1D*)h_hitT_ID_MDT.Clone("h_hitT_ID_WCSim"));

  TH1D h_hitT_OD_MDT;
  h_hitT_OD_MDT.SetNameTitle("h_hitT_OD_MDT","h_hitT_OD_MDT");
  h_hitT_OD_MDT.SetBins(100,0,10000);
  TH1D h_hitT_OD_WCSim = *((TH1D*)h_hitT_OD_MDT.Clone("h_hitT_OD_WCSim"));

  // Digi hit charge distribution
  TH1D h_hitQ_ID_MDT;
  h_hitQ_ID_MDT.SetNameTitle("h_hitQ_ID_MDT","h_hitQ_ID_MDT");
  h_hitQ_ID_MDT.SetBins(100,0,10000);
  TH1D h_hitQ_ID_WCSim = *((TH1D*)h_hitQ_ID_MDT.Clone("h_hitQ_ID_WCSim"));

  TH1D h_hitQ_OD_MDT;
  h_hitQ_OD_MDT.SetNameTitle("h_hitQ_OD_MDT","h_hitQ_OD_MDT");
  h_hitQ_OD_MDT.SetBins(100,0,1000);
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

  // Input should have 4 arguments
  if(argc != 4){
    std::cout << "Command should include executable, MDT input file, WCSim input file and output file!" << std::endl;
    exit(1);
  }  

  // Read input arguments
  std::string fin_MDT_name = argv[1];
  std::string fin_WCSim_name = argv[2];
  std::string fout_name = argv[3];

  std::cout << "---------------------------------" << std::endl;
  std::cout << "Start running MDT electroincs sim check" << std::endl;
  std::cout << "---------------------------------" << std::endl;  


  RunSingleFile(fin_MDT_name,fin_WCSim_name,fout_name);



  std::cout << "---------------------------------" << std::endl;
  std::cout << "Finish running MDT electroincs sim check" << std::endl;
  std::cout << "---------------------------------" << std::endl;
   
  return 0;

}