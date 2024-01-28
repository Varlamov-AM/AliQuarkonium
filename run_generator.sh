#! /bin/bash

START_DIR="$PWD"

cd AliEventLib

cd build

CURR_DIR="$PWD"

LD_LIBRARY_PATH=$D_LIBRARY_PATH:$CURR_DIR:/etc/Pythia8/pythia8308/lib/

cd $START_DIR

cd AliEventGenerator

make -j8

./main.exe 30000


