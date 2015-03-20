#!/bin/bash

echo "***Generate config files nsets.conf and ssets.conf***"
g++ -std=c++11 ConnGen.cpp
time ./a.out

echo "***Execute insilico***"
time ./insilico.out sp.dat nsets.conf ssets.conf 

echo "***Plot data***"
time gnuplot "plot"

echo "***Done***"
python sms.py
