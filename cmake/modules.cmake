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
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required( VERSION 3.16 )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules )

function( add_module name fname )
    file( MAKE_DIRECTORY ${PREBUILT_MODULE_PATH} )

    if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
        add_custom_target( ${name}.pcm
            COMMAND
                ${CMAKE_CXX_COMPILER}
                -std=c++20
                -stdlib=libc++
                -fmodules
                -fbuiltin-module-map
                -fmodules-ts
                -Xclang -emit-module-interface
                -fprebuilt-module-path=${PREBUILT_MODULE_PATH}
                -c
                ${CMAKE_CURRENT_SOURCE_DIR}/${fname}
                -o ${PREBUILT_MODULE_PATH}/${name}.pcm
        )

    elseif( CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" )
        message( FATAL_ERROR "C++20 modules are broken in Apple Clang right now" )

    elseif( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
        add_custom_target( ${name}.pcm
            COMMAND
                ${CMAKE_CXX_COMPILER}
                -std=c++20
                -fmodules-ts
                -c
                ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
                -o ${name}.pcm
        )

    elseif( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
        add_custom_target( ${name}.obj
            COMMAND
                ${CMAKE_CXX_COMPILER}
                /experimental:module
                /c
                ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
        )

    else()
        message( FATAL_ERROR "Compiler not supported for C++20 modules" )

    endif()
endfunction( add_module )

function( add_module_dependencies target )
    if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
        target_compile_options( ${target} PRIVATE
            -std=c++20
            -stdlib=libc++
            -fmodules
            -fmodules-ts
            -fbuiltin-module-map
            -fprebuilt-module-path=${PREBUILT_MODULE_PATH}
        )
        add_dependencies( ${target} ${ARGN} )

    elseif( CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" )
        message( FATAL_ERROR "C++20 modules are broken in Apple Clang right now" )

    elseif( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
        message( FATAL_ERROR "C++20 modules for MSVC (in this cmake file) not implemented / tested yet" )

    elseif( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
        message( FATAL_ERROR "C++20 modules for GNU (in this cmake file) not implemented / tested yet" )

    else()
        message( FATAL_ERROR "Compiler not supported for C++20 modules" )

    endif()
endfunction( add_module_dependencies )


# GNU
#  add_compile_options( -fmodules-ts )
#  add_module( foo foo.cpp )
#  add_executable( the-exe main.cpp )
#  add_custom_target( module foo.cpp )
#  target_link_options( main PUBLIC "LINKER:foo.pcm" )
#  add_dependencies( main foo.pcm )

# MSVC
#  add_compile_options( /experimental:module /c )
#  add_module( foo foo.cpp )
#  add_module( bar bar.cpp )
#  add_executable( the-exe main.cpp )
#  add_dependencies( main foo.pcm bar.pcm )


