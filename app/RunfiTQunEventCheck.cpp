#include <iostream>
#include <sstream>
#include <string>

#include "analysis/fiTQunEventCheck.h"

// This script checks fiTQun reconstructed events

int main(int argc, char **argv){

  // Input should have 3 arguments
  if(argc != 3){
    std::cout << "Command should include executable, input file list, and output file!" << std::endl;
    exit(1);
  }

  // Read input arguments
  std::string fin_list_name = argv[1];
  std::string fout_name = argv[2];  

  std::cout << "---------------------------------" << std::endl;
  std::cout << "Start running fiTQun event check" << std::endl;
  std::cout << "---------------------------------" << std::endl;

  // Initialize the analysis class
  fiTQunEventCheck *analysis = new fiTQunEventCheck(fin_list_name,fout_name);

  // Run the analysis
  analysis->RunAnalysis();

  // Delete analysis
  delete analysis;

  std::cout << "---------------------------------" << std::endl;
  std::cout << "Finish running fiTQun event check" << std::endl;
  std::cout << "---------------------------------" << std::endl;

  return 0;

}