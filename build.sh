#!/bin/bash

if [ ! -d build ]; then
    mkdir build
fi

cd build
cmake .. 

if ((!$?)); then
    cmake --build . 
else 
    echo "FAILED TO RUN"
fi
