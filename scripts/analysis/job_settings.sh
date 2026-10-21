#!/bin/bash
#$ -q hep.q
#$ -l h_rt=1:00:00
#$ -l h_vmem=4G
#$ -o /vols/hyperk/users/xzhao/HK/IWCD/selection_output/fiTQun_event_check/log/
#$ -e /vols/hyperk/users/xzhao/HK/IWCD/selection_output/fiTQun_event_check/log/

# Setup the environment
source /home/hep/xzhao6/HK/IWCD/SelectionScript/scripts/setup/setup_ICL_LX.sh

# Run the executable
if [ ${1} = "1" ]
then
  RunfiTQunEventCheck ${2} ${3}
fi
