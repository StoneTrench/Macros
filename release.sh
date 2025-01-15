#!/bin/bash

# Ensure build directory exists
mkdir -p build
cd build || exit 1

# Configure and build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build . || exit 1

# Release directory is now ready
echo "Release build is ready in the 'release' directory."