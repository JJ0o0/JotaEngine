#!/bin/bash

mkdir -p build # Se não tiver
cd build
cmake ..
make
cd ..
clear
./build/JotaEngine
