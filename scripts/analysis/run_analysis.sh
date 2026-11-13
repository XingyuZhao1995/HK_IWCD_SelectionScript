#!/bin/bash

# Source the environment
source /vols/hyperk/users/xzhao/HK/IWCD/SelectionScript/scripts/setup/setup_ICL_LX.sh

# Run the executable
if [ ${1} = "1" ]
then
  RunfiTQunEventCheck ${2} ${3}
elif [ ${1} = "2" ]
then
  RunMDTEventCheck ${2} ${3}
fi
