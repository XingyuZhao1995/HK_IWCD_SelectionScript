#!/bin/bash

# Choose analysis option
# 1 = check fiTQun output events, 2 = check MDT output events
Option=${1}
# Suboption (1 = WCSim + fiTQun, 2 = WCSim + MDT + fiTQun)
SubOption=${2}

# Input file path
InputWCSimPath=""
InputMDTPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/MDT_output/pileup"
InputfiTQunPath=""
if [ ${SubOption} = "1" ]
then
  InputWCSimPath="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/ID/flux23av1_p320_nd25/rwcs"
  InputfiTQunPath="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/fitqun_6.4.4_cfqni.1.1.1.1.2/ID/flux23av1_p320_nd25/rfqn"
elif [ ${SubOption} = "2" ]
then
  InputWCSimPath="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/ID/flux23av1_p320_nd25/rwcs"
  InputfiTQunPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/fiTQun_output/oneone"
fi

# File list path
FileListPath="/vols/hyperk/users/xzhao/HK/IWCD/SelectionScript/scripts/analysis/file_list"

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
NJobs=800
if [ ${Option} = "1" ]
then
  NFilePerList=40
  NJobs=20
elif [ ${Option} = "2" ]
then
  NFilePerList=2
  NJobs=40
fi

# Loop over input files
FileCount=0
OutIndex=0
if [ ${Option} = "1" ]
then

  for File in ${InputfiTQunPath}/*.root
  do
    # Extract the common pattern
    BaseName="${File##*/}"
    CorrFile="${InputWCSimPath}/${BaseName%_rfqn.root}_rwcs.root"
    if [ ! -f "${CorrFile}" ]
    then
      echo "WARNING: no matching file ${CorrFile}, skipping ${File}"
      continue
    fi

    # Update file count
    FileCount=$(($FileCount + 1))

    # Save the input file path to the file list
    echo "${CorrFile} ${File}" >> ${FileListPath}/${OutIndex}.txt

    # For every specific amount of files, put their paths into the same list
    if (($FileCount % $NFilePerList == 0))
    then
      # Update file list index
      OutIndex=$(($OutIndex + 1))
      # Exit if job number reached
      if [ ${OutIndex} -ge "${NJobs}" ]
      then
        break
      fi         
    fi
  done

elif [ ${Option} = "2" ]
then

  for File in ${InputMDTPath}/*.root
  do
    # Update file count
    FileCount=$(($FileCount + 1))

    # Save the input file path to the file list
    echo "${File}" >> ${FileListPath}/${OutIndex}.txt

    # For every specific amount of files, put their paths into the same list
    if (($FileCount % $NFilePerList == 0))
    then
      # Update file list index
      OutIndex=$(($OutIndex + 1))
    fi
  done

fi

# Output file path
OutputPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/selection_output"
if [ ${Option} = "1" ]
then
  OutputPath="${OutputPath}/fiTQun_event_check"
  if [ ${SubOption} = "1" ]
  then
    OutputPath="${OutputPath}/WCSim_ele"
  elif [ ${SubOption} = "2" ]
  then
    OutputPath="${OutputPath}/MDT_ele"
  fi
elif [ ${Option} = "2" ]
then
  OutputPath="${OutputPath}/MDT_event_check"
fi
# (Delete existing output files)
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
  echo "${Option} ${List} ${OutputPath}/${FileName}" >> ${SummaryFile}

done

# Delete existing log files as well
rm -rf /vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/selection_output/logs/*
