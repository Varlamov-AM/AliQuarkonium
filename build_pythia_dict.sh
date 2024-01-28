#! /bin/bash

ls -l

STARTDIR="$PWD"

cd AliEventLib

rm -rf build

ls -l

mkdir build
cd build

cmake ..

make -j8
