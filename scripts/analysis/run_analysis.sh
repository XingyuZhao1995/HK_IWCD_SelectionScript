#!/bin/bash

# Choose analysis option
# 1 = check fiTQun output events
Option=${1}

# Input file list path
FileListPath="/home/hep/xzhao6/HK/IWCD/SelectionScript/scripts/analysis/file_list"
# Path to output files
OutputPath="/vols/hyperk/users/xzhao/HK/IWCD/selection_output/fiTQun_event_check"

# Loop over file lists
OutIndex=0
for List in ${FileListPath}/*.txt
do

  # Output file name
  OutputName="${OutputPath}/${OutIndex}.root"

  # Submit the program
  qsub job_settings.sh ${Option} ${List} ${OutputName}

  # Update index
  OutIndex=$(($OutIndex + 1))

done
