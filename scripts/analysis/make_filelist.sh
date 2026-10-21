#!/bin/bash

# Input file path
InputPath="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/fitqun_6.4.4_cfqni.1.1.1.1.2/ID/flux23av1_p320_nd25/rfqn"
FileListPath="./file_list"

# Create file list directory if not exist
if [ ! -d ${FileListPath} ]
then
  mkdir -p ${FileListPath}
fi

# Delete existing file lists
rm -rf ${FileListPath}/*.txt

# How many files to be put in each list
NFilePerList=500

# Loop over input files
FileCount=0
OutIndex=0
for File in ${InputPath}/*.root
do

  # Update file count
  FileCount=$(($FileCount + 1))

  # For every specific amount of files, put their paths into the same list
  if (($FileCount % $NFilePerList == 0))
  then
    # Update file list index
    OutIndex=$(($OutIndex + 1))
  fi

  # Save the input file path to the file list
  echo "${File}" >> ${FileListPath}/${OutIndex}.txt

done
