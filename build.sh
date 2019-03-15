#!/usr/bin/env bash
####
# Description.
####

set -e
pushd $(dirname $0) > /dev/null

mkdir -p build
cd build

g++ ../source/*.cpp -std=c++11 -O3 -flto -Wpedantic -Wall -Wextra -I ../include -o test

echo "===="
./test
echo "===="

popd > /dev/null
