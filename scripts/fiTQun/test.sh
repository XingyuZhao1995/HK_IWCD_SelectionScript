#!/bin/bash

# Input file
InputFile="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/MDT_output/oneone/beam_neut_iwcd_p320_nd25_00000000-0004_rmdt.root"

# Config file
ConfigFile="/vols/hyperk/users/xzhao/HK/IWCD/SelectionScript/scripts/fiTQun/IWCD_mPMT_WithOD.parameters.dat"

# Run the program
runfiTQun -p ${ConfigFile} -r test.root ${InputFile}
