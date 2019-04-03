#!/usr/bin/env bash
####
# Uses GCC to compile all source files into a build directory.
# Runs a test if the build succeeds.
####

# Silently go to directory of this script
pushd $(dirname $0) > /dev/null

# Create "build" directory if it doesn't already exist
mkdir -p build

# Compile source into build directory and record exit status
g++-8 source/test.cpp  -std=c++17  -O3 -ffast-math  -Wpedantic -Wall -Wextra  -I include  -o build/test
COMPILE_ERROR=$?

# Things to do if compilation succeeded
if [ $COMPILE_ERROR -eq 0 ]; then
    # Create inspection files for executable debug
    objdump --syms build/test > build/inspect.txt
    # Run a test
    echo "===="
    ./build/test
    echo "===="
else
    echo "(skipping run)"
fi

# Silently return to caller directory
popd > /dev/null
