#!/usr/bin/env bash
####
#
####

set -e

g++ source/test.cpp -std=c++11 -O3 -I include -o build/test

./build/test
