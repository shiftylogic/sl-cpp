#!/usr/bin/env bash

CMAKE_ROOT=$PWD/.tools/cmake/CMake.app/Contents
TOOLCHAIN_ROOT=$PWD/.tools/llvm

mkdir -p build
cd build

${CMAKE_ROOT}/bin/cmake \
  -G Ninja \
  -DCMAKE_C_COMPILER=${TOOLCHAIN_ROOT}/bin/clang \
  -DCMAKE_CXX_COMPILER=${TOOLCHAIN_ROOT}/bin/clang++ \
  ..

