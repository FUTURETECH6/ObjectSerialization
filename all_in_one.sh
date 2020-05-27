#!/bin/zsh
mkdir -p build
cd build
cmake ..
make
cd ..
rm -rf build
rm -rf Sample_Output
mkdir Sample_Output
./bin/test &> ./Sample_Output/Output_test.txt
rm -rf bin
