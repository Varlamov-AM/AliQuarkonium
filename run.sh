#! /bin/bash

ls -l
echo "Let's begin!" 

STARTDIR="$PWD"

cd AliEventLib

rm -rf build

ls -l

mkdir build
cd build

cmake ..

make -j8
CURR_DIR="$PWD"

LD_LIBRARY_PATH=$D_LIBRARY_PATH:$CURR_DIR:/etc/Pythia8/pythia8308/lib/

ls -l

cd $STARTDIR

#cd AliEventGenerator

#make -j8

#./main.exe 2000000

cd AliEventAnalysis

make -j8 

./main.exe

#root -l test.cpp
