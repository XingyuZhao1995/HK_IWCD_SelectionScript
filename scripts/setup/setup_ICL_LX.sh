#!/bin/bash

# Initialize ROOT
source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.40.04/x86_64-almalinux9.8-gcc115-opt/bin/thisroot.sh

# Add library path to LD_LIBRARY_PATH
LibraryPath="/home/hep/xzhao6/HK/IWCD/SelectionScript/install/lib64"
export LD_LIBRARY_PATH=${LibraryPath}:${LD_LIBRARY_PATH:-}

# Add executable path to PATH
ExecutablePath="/home/hep/xzhao6/HK/IWCD/SelectionScript/install/bin"
export PATH=${ExecutablePath}:${PATH:-}
