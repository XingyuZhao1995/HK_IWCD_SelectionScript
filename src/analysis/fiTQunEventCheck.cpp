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





}

// ********************************************************
void fiTQunEventCheck::RunEventAnalysis(AnafiTQunEvent &event){
// ********************************************************






}

// ********************************************************
void fiTQunEventCheck::SaveOutputFile(){
// ********************************************************

  fout->cd();
  tout->Write();
  fout->Close();

}