#!/bin/bash

# Create documentation.
#mkdir -p doc
#cd doc
#doxygen
#cd ..

# Compile.
cmake -B build -DCMAKE_BUILD_TYPE=Release .
cmake --build build

# Start program.
./build/ld49
