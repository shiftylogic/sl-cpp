/**
 * MIT License
 *
 * Copyright (c) 2023-present Robert Anderson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __MAPPED_FILE_H_30E530145D4241DEAC960482AF936880__
#define __MAPPED_FILE_H_30E530145D4241DEAC960482AF936880__

#include "error.h"

namespace sl::io
{

    enum class CacheHint
    {
        Default,
        Random,
        Sequential,
    };

}

#if defined( _WIN32 )
#    include "win/mapped-file.h"
#elif defined( __linux__ ) || defined( __APPLE__ )
#    include "unix/mapped-file.h"
#else
#    error File mapping / views not implememented for the target platform.
#endif

#endif /* __MAPPED_FILE_H_30E530145D4241DEAC960482AF936880__ */