#! /bin/bash

cd AliEventLib

rm -rf build

mkdir build
cd build

cmake ..

make -j8
