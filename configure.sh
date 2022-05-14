
#/bin/bash

# clear cmake cache before configure
rm -f ./out/build/CMakeCache.txt

# cmake -DUSE_ADDER=OFF -S . -B out/build 
cmake -S . -B out/build 