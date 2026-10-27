#ifndef BASEFITQUNANALYSIS_H
#define BASEFITQUNANALYSIS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <filesystem>

#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>

#include "fiTQun_project/fiTQun_projectProjectHeaders.h"
#include "base/AnafiTQunEvent.h"
#include "utils/FillInfoUtils.h"
#include "utils/MiscUtils.h"

const int NMAXCLUS = 6;
const int NMAXTIMEWIN = 7;
const int NMAXPEAK = 10;
const int NMAXSUBEVE = 10;
const int NPIDHYPO = 7;
const int NMAXMRFIT = 50;

// Base class to analyze fiTQun output file
class BasefiTQunAnalysis{

public:

  // Constructor
  BasefiTQunAnalysis(std::string in_list_name){
    fin_list_name = in_list_name;
  };
  // Destructor
  virtual ~BasefiTQunAnalysis(){};

  // Debug tag
  const bool DEBUG = false;
  
  // Run the analysis
  void RunAnalysis();

  // ----------------------------------------------
  // To be implemented in inherited classes
  
  // Overall initialization
  virtual void OverallInitialization() = 0;
  
  // Run event analysis
  virtual void RunEventAnalysis(AnafiTQunEvent &event) = 0;  

  // Save output file
  virtual void SaveOutputFile() = 0;

private:

  // Input file list name
  std::string fin_list_name;
  
  // ----------------------------------------------
  // Analysis functions
  
  // Loop over input files
  void RunInputFileLoop();
  // Single file analysis
  void RunSingleFile(std::string file_WCSim_name, std::string file_fiTQun_name);  

  // Examine if WCSim and fiTQun entries correspond to the same event
  bool IsSameEvent();

  // ----------------------------------------------
  // Input tree branch variables

  // WCSim file
  // (Geometry tree)
  WCSimRootGeom *WCSim_geom;

  // (WCSim tree)
  WCSimRootEvent *WCSim_ID_event;
  WCSimRootTrigger *WCSim_ID_trigger;
  WCSimRootEvent *WCSim_OD_event;
  WCSimRootTrigger *WCSim_OD_trigger;

  // fiTQun file
  // (NEUT RooTracker tree)
  ND::NRooTrackerVtx *NRooTrackerVtx;

  // (fiTQun tree)
  int nevt;

  int cluster_ncand;
  float cluster_tstart[NMAXCLUS];
  float cluster_tend[NMAXCLUS];
  int cluster_nhits[NMAXCLUS];
  float cluster_totq[NMAXCLUS];

  int fqntwnd;
  int fqtwnd_iclstr[NMAXTIMEWIN];
  int fqtwnd_npeak[NMAXTIMEWIN];
  float fqtwnd[NMAXTIMEWIN][2];
  float fqtwnd_peakt0[NMAXTIMEWIN][NMAXPEAK];  

  int fqnse;
  int fqnhitpmt[NMAXSUBEVE];
  float fqtotq[NMAXSUBEVE];
  int fqitwnd[NMAXSUBEVE];
  int fqipeak[NMAXSUBEVE];  

  int fq1rpcflg[NMAXSUBEVE][NPIDHYPO]; 
  float fq1rmom[NMAXSUBEVE][NPIDHYPO];
  float fq1rnll[NMAXSUBEVE][NPIDHYPO];
  float fq1rpos[NMAXSUBEVE][NPIDHYPO][3];
  float fq1rdir[NMAXSUBEVE][NPIDHYPO][3];

  int fqnmrfit;
  int fqmrifit[NMAXMRFIT];
  int fqmrnring[NMAXMRFIT];
  int fqmrpcflg[NMAXMRFIT];
  float fqmrnll[NMAXMRFIT];

  int fqpi0pcflg[2];
  float fqpi0nll[2];

  int muechk_ncand[NMAXCLUS];

};

#endif