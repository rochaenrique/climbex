#!/bin/bash

if [ ! -d build ]; then
    mkdir build
fi

cd build
cmake -DCBX_EXAMPLES=True .. 

if ((!$?)); then
    cmake --build .  
else 
    echo "FAILED TO RUN"
fi
