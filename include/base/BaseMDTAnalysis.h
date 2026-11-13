#ifndef BASEMDTANALYSIS_H
#define BASEMDTANALYSIS_H

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
#include "base/AnaMDTEvent.h"
#include "utils/FillInfoUtils.h"
#include "utils/MiscUtils.h"

const int NMAXINT = 20;
const int NMAXTRACKS = 20000;

// Base class to analyze MDT output file
class BaseMDTAnalysis{

public:

  // Constructor
  BaseMDTAnalysis(std::string in_list_name);
  // Destructor
  virtual ~BaseMDTAnalysis();

  // Debug tag
  const bool DEBUG = false;
  
  // Run the analysis
  void RunAnalysis();

  // ----------------------------------------------
  // To be implemented in inherited classes
  
  // Overall initialization
  virtual void OverallInitialization() = 0;
  
  // Run event analysis
  virtual void RunEventAnalysis(AnaMDTEvent &event) = 0;

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
  void RunSingleFile(std::string file_name);  

  // ----------------------------------------------
  // Input tree branch variables

  // WCSim-like tree
  WCSimRootEvent *WCSim_ID_event = nullptr;
  WCSimRootTrigger *WCSim_ID_trigger = nullptr;
  WCSimRootEvent *WCSim_OD_event = nullptr;
  WCSimRootTrigger *WCSim_OD_trigger = nullptr;  

  // Pile-up info tree
  int NNuIntTot;
  int NIDNuInt;
  int NBeamBkg;
  int FileIdNum[NMAXINT];
  int EventIdNum[NMAXINT];
  int NeutCode[NMAXINT];
  float NuDir[NMAXINT][3];
  float NuEne[NMAXINT];
  int NuIntBunch[NMAXINT];
  float NuIntTime[NMAXINT];
  int NuPDG[NMAXINT];
  float NuPos[NMAXINT][3];

  int NTracks;
  int TrackNuIntIdx[NMAXTRACKS];

  std::vector<int> *PENuIntIdx = 0;
  std::vector<int> *PENuIntIdx_OD = 0;  

};

#endif