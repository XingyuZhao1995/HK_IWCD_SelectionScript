#!/bin/bash

# Input file path
InputPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/MDT_output/oneone"
FileListPath="/vols/hyperk/users/xzhao/HK/IWCD/SelectionScript/scripts/fiTQun/file_list"

# Output file path
OutputPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/fiTQun_output/oneone"

# Create file list directory if not exist
if [ ! -d ${FileListPath} ]
then
  mkdir -p ${FileListPath}
fi

# Delete existing file lists
rm -rf ${FileListPath}/*.txt

# How many files to be put in each list
NFilePerList=1
# How many jobs to be submitted
NJobs=200

# Loop over input files
FileCount=0
JobIndex=0
for File in ${InputPath}/*.root
do
  
  # Extract the common pattern
  BaseName="${File##*/}"
  CorrFile="${OutputPath}/${BaseName%_rmdt.root}_rfqn.root"

  # Update file count
  FileCount=$(($FileCount + 1))

  # Save the input file path to the file list
  echo "${File} ${CorrFile}" >> ${FileListPath}/${JobIndex}.txt 

  # For every specific amount of files, put their paths into the same list
  if (($FileCount % $NFilePerList == 0))
  then
    # Update file list index
    JobIndex=$(($JobIndex + 1))
    # Exit if job number reached
    if [ ${JobIndex} -ge "${NJobs}" ]
    then
      break
    fi        
  fi

done

# Delete existing output files
rm -rf ${OutputPath}/*.root

# A summary file to put input file lists
SummaryFile="file_list.txt"
if [ -f ${SummaryFile} ]
then
  rm -f ${SummaryFile}
fi

# Loop over input config lists
for List in ${FileListPath}/*.txt
do
  echo "${List}" >> ${SummaryFile}
done

# Delete existing log files as well
rm -rf /vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/fiTQun_output/logs/*
