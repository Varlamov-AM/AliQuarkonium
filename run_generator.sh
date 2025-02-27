#! /bin/bash

source ./add_shared_lib.sh

cd AliEventGenerator

make -j8

./main.exe 10000


