#!/bin/bash

# Input file path
InputMDTPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/MDT_output/oneone"
InputWCSimPath="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/ID/flux23av1_p320_nd25/rwcs"
FileListPath="/vols/hyperk/users/xzhao/HK/IWCD/SelectionScript/scripts/analysis/file_list"

# Output file path
OutputPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/selection_output/quick_check"

# Create file list directory if not exist
if [ ! -d ${FileListPath} ]
then
  mkdir -p ${FileListPath}
fi

# Delete existing file lists
rm -rf ${FileListPath}/*.txt

# How many files to be put in each list
NFilePerList=10

# Loop over input files
FileCount=0
OutIndex=0
for File in ${InputMDTPath}/*.root
do

  # Extract the common pattern
  BaseName="${File##*/}"
  CorrFile="${InputWCSimPath}/${BaseName%_rmdt.root}_rwcs.root"
  if [ ! -f "${CorrFile}" ]
  then
    echo "WARNING: no matching file ${CorrFile}, skipping ${File}"
    continue
  fi  
  OutputName="${OutputPath}/${FileCount}.root"

  # Update file count
  FileCount=$(($FileCount + 1))

  # For every specific amount of files, put their paths into the same list
  if (($FileCount % $NFilePerList == 0))
  then
    # Update file list index
    OutIndex=$(($OutIndex + 1))
  fi

  # Save the input file path to the file list
  echo "${File} ${FilCorrFilee} ${OutputName}" >> ${FileListPath}/${OutIndex}.txt

done

# Delete existing output files
rm -rf ${OutputPath}/*.root

# A summary file to put input file lists and output files
SummaryFile="file_list.txt"
if [ -f ${SummaryFile} ]
then
  rm -f ${SummaryFile}
fi

# Loop over input file lists
for List in ${FileListPath}/*.txt
do

  # Make output file name
  FileNameFull="${List##*/}"
  FileName="${FileNameFull%.txt}.root"

  # Save input and output path to the file list
  echo "${List}" >> ${SummaryFile}

done

# Delete existing log files as well
rm -rf /vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/selection_output/logs/*
