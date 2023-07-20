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

project( sl-uv )

add_library( ${PROJECT_NAME} )
target_link_libraries( ${PROJECT_NAME} PUBLIC
    sl-core
    uv_a
)
target_sources( ${PROJECT_NAME} PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    FILES
        src/mod.cpp
        src/error.cpp
        src/handle.cpp
        src/loop.cpp
        src/idler.cpp
        src/signaler.cpp
        src/timer.cpp
)

enable_warnings( ${PROJECT_NAME} )


###################
#
# Build tests

set( SLUV_LIB_TEST_SRCS
    "tests/idler-test.cpp"
    "tests/timer-test.cpp"
)

build_tests(
    NAME uv-tests
    SOURCES ${SLUV_LIB_TEST_SRCS}
    LIBRARIES ${PROJECT_NAME}
)


###################
#
# Build examples

add_example(
    NAME loop-demo
    SOURCES examples/loop-demo.cpp
    LIBRARIES sl-core ${PROJECT_NAME}
)

