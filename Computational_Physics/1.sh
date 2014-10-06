#!/bin/bash

make clean
make
echo "Running randomz.out"
./bin/randomz > stdout.txt < stdin.txt
echo "Running atof.out"
./bin/atof > randomz.binary < stdout.txt
echo "Running schrage.out"
./bin/schrage
echo "Invoking MATLAB"
matlab -nodisplay -nojvm -nodesktop -r "run('./MATLAB_Script/script_1.m');exit;"
rm schrage.binary randomz.binary stdout.txt
make clean

# Test have been performed on both my mac and pulsar.bao.ac.cn running CentOS6
