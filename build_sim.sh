#!/bin/bash

# Cadmium path on devssim
CADMIUM_PATH="/home/cadmium/rt_cadmium/include"

# Compile
g++ -g -O3 -std=c++17 ./main/main.cpp -I $CADMIUM_PATH -o simulation

echo "Build successful! Run it using: ./simulation"