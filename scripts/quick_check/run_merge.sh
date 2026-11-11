#!/bin/bash

# Input file path
InputPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/selection_output/quick_check"

# Output file path
OutputPath="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/selection_output"

# Temporary file list
TmpList="tmp_list.txt"
if [ -f "${TmpList}" ]
then
  rm -f ${TmpList}
fi

# Loop over input files
for File in ${InputPath}/*.root
do
  echo "${File}" >> ${TmpList}
done

# Run merging
RunMDTEleSimQuickCheck 2 ${TmpList} ${OutputPath}/merged_quick_check.root
