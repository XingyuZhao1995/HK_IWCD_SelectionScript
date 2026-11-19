#!/bin/bash

# Source environment
source /usr/local/hk/hk-pilot/setup.sh
source /usr/local/hk/hk-software/install-Linux_x86_64-gcc_8-python_3.8.13/setup.sh 

# Source WCSim
source /vols/hyperk/users/xzhao/HK/IWCD/IWCDSoftware/WCSim/install/bin/this_wcsim.sh

# Source fiTQun
# FITQUN_ROOT: where fiTQun looks for fiTQun.parameters.dat and the const/ tune files
# (the HK-Pilot CMake build does not generate this_fitqun.sh, so set it by hand)
export FITQUN_ROOT="/vols/hyperk/users/xzhao/HK/IWCD/IWCDSoftware/fiTQun"
fiTQunPath="${FITQUN_ROOT}/install/bin"
export PATH=${fiTQunPath}:${PATH:-}
