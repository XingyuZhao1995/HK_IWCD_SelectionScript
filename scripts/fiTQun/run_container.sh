#!/bin/bash

# File list
FileList=${1}

source /usr/local/hk/hk-pilot/setup.sh
source /usr/local/hk/hk-software/install-Linux_x86_64-gcc_8-python_3.8.13/setup.sh 

# Source WCSim
source /vols/hyperk/users/xzhao/HK/IWCD/IWCDSoftware/WCSim/install/bin/this_wcsim.sh

# Source fiTQun
export FITQUN_ROOT="/vols/hyperk/users/xzhao/HK/IWCD/IWCDSoftware/fiTQun"
fiTQunPath="${FITQUN_ROOT}/install/bin"
export PATH=${fiTQunPath}:${PATH:-}

# Config file
ConfigFile="/vols/hyperk/users/xzhao/HK/IWCD/SelectionScript/scripts/fiTQun/IWCD_mPMT_WithOD.parameters.dat"

# Read file list line by line
while read -r Input Output
do
  # Run the program
  runfiTQun -p ${ConfigFile} -r ${Output} ${Input}
done < ${FileList}
