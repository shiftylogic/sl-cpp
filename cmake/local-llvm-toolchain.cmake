# MIT License
#
# Copyright (c) 2022 Robert Anderson
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FOM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.



#####################################
#
# Local toolchain path

set( TOOLCHAIN_DIR "${CMAKE_SOURCE_DIR}/.tools/llvm" )
message( STATUS "Using toolchain path: ${TOOLCHAIN_DIR}" )


#####################################
#
# Setup CMake CMAKE_FIND_ROOT_PATH

# set( CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_DIR} )
# set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
# set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH )
# set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH )


#####################################
#
# Discover all the tools

set( CMAKE_C_COMPILER "${TOOLCHAIN_DIR}/bin/clang" )
set( CMAKE_CXX_COMPILER "${TOOLCHAIN_DIR}/bin/clang++" )

# find_program( CMAKE_C_COMPILER      NAMES   clang           PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( CMAKE_CXX_COMPILER    NAMES   clang++         PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( CMAKE_STRIP           NAMES   llvm-strip      PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( AS                    NAMES   llvm-as         PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( AR                    NAMES   llvm-ar         PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( OBJCOPY               NAMES   llvm-objcopy    PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( OBJDUMP               NAMES   llvm-objdump    PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( SIZE                  NAMES   llvm-size       PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)
# find_program( LD                    NAMES   lld             PATHS  ${TOOLCHAIN_DIR}/bin    NO_DEFAULT_PATH)

# set( CMAKE_C_COMPILER_EXTERNAL_TOOLCHAIN ${TOOLCHAIN_DIR} )
# set( CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN ${TOOLCHAIN_DIR} )


#####################################
#
# Setup include and lib paths

# message( STATUS "Prefix: ${CMAKE_SYSTEM_PREFIX_PATH}" )
# set( CMAKE_PREFIX_PATH "${CMAKE_SYSTEM_PREFIX_PATH}/include" )

