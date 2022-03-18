#!/usr/bin/env bash

export CROOT=$(pwd)

cmake -S . -B build

cd build && make && cd ..

echo "$CROOT"
./build/ImageServer