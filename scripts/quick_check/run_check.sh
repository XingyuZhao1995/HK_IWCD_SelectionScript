#!/bin/bash

# File list
FileList=${1}

# Source the environment
source /vols/hyperk/users/xzhao/HK/IWCD/SelectionScript/scripts/setup/setup_ICL_LX.sh

# Read file list line by line
while read -r Input_MDT Input_WCSim Output
do
  # Run the program
  RunMDTEleSimQuickCheck 1 ${Input_MDT} ${Input_WCSim} ${Output}
done < ${FileList}
