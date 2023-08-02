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

project( sl-core )

add_library( ${PROJECT_NAME} )
target_link_libraries( ${PROJECT_NAME} PUBLIC
    json
)
target_sources( ${PROJECT_NAME} PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    FILES
        src/config/mod.cpp
        src/config/json.cpp
        src/config/values.cpp

        src/io/mod.cpp
        src/io/cache-hint.cpp
        src/io/error.cpp
        src/io/load.cpp
        src/io/unix/mapped-file.cpp     # TODO: Pick the 'win' files on Windows
        src/io/unix/mapped-view.cpp

        src/logging/mod.cpp
        src/logging/logger.cpp

        src/mem/mod.cpp
        src/mem/allocator.cpp

        src/utils/mod.cpp
        src/utils/fs.cpp
        src/utils/lazy.cpp
        src/utils/noncopyable.cpp
        src/utils/pointers.cpp
        src/utils/strings.cpp
)

enable_warnings( ${PROJECT_NAME} )


###################
#
# Build tests

set( SLCORE_LIB_TEST_SRCS
    "tests/allocator-test.cpp"
    "tests/config-test.cpp"
    "tests/lazy-test.cpp"
    "tests/strings-test.cpp"
)

build_tests(
    NAME core-tests
    SOURCES ${SLCORE_LIB_TEST_SRCS}
    LIBRARIES ${PROJECT_NAME}
)
