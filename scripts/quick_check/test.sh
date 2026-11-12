#!/bin/bash

InputMDTFile="/vols/hyperk/users/xzhao/HK/IWCD/OutputFiles/MDT_output/oneone/beam_neut_iwcd_p320_nd25_00000000-0004_rmdt.root"
InputWCSimFile="/vols/hyperk/hk-neut.5.6.4.4-1_p7c1/IWCD_geom_v3_hz4930_r4640/wcsim_v1.12.35_cwcs1.1.1.1/ID/flux23av1_p320_nd25/rwcs/beam_neut_iwcd_p320_nd25_00000000-0004_rwcs.root"

RunMDTEleSimQuickCheck 1 ${InputMDTFile} ${InputWCSimFile} test.root
