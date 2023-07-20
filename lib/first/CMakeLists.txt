# MIT License
#
# Copyright (c) 2023-present Robert Anderson
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

cmake_minimum_required( VERSION 3.26 )

project( first )


###################
#
# Build 'one' module

add_library( one )
target_sources( one PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    FILES
        src/one.cpp
)


###################
#
# Build 'main' executable

add_executable( main
    src/main.cpp
)
target_link_libraries( main PRIVATE
    one
)


###################
#
# Build tests

# set( FIRST_LIB_TEST_SRCS
#     tests/first_test.cpp
# )

# build_tests(
#     NAME first-tests
#     SOURCES ${FIRST_LIB_TEST_SRCS}
#     LIBRARIES ${PROJECT_NAME}
# )
