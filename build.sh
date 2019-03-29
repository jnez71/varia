#!/usr/bin/env bash
####
# Uses GCC to compile varia source into a "build" directory.
# Runs a test if the build succeeds.
####

pushd $(dirname $0) > /dev/null

mkdir -p build

g++ source/*.cpp  -std=c++14  -O3 -ffast-math -flto  -Wpedantic -Wall -Wextra  -I include  -o build/test

if [ $? -eq 0 ]; then
    echo "===="
    ./build/test
    echo "===="
else
    echo "(skipping run)"
fi

popd > /dev/null
