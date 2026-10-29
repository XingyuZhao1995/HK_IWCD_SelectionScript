#!/bin/bash

Option=${1}

InputWCSimFile="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/ID/flux23av1_p320_nd25/rwcs/beam_neut_iwcd_p320_nd25_00000000-0010_rwcs.root"
InputfiTQunFile="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/fitqun_6.4.4_cfqni.1.1.1.1.2/ID/flux23av1_p320_nd25/rfqn/beam_neut_iwcd_p320_nd25_00000000-0010_rfqn.root"

TmpFile="temp.txt"

echo "${InputWCSimFile} ${InputfiTQunFile}" >> ${TmpFile}

if [ ${Option} = "1" ]
then
  RunNumuCCQESelection ${TmpFile} test.root
fi

rm -f ${TmpFile}
