#! /bin/bash

source add_shared_lib.sh 

cd AliEventAnalysis

make -j8 

./main.exe $ALI_QUARKONIUM/AliEventGenerator/

