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

module;

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


export module sl.io:mapped_file;

import sl.utils;
import :cache_hint;
import :error;
import :mapped_view;


namespace sl::io
{

    export struct mapped_file : sl::utils::noncopyable
    {
    public:
        mapped_file( const char* name, cache_hint hint = cache_hint::none )
            : _hint { MADV_NORMAL }
            , _fd { -1 }
            , _size { 0 }
        {
            _fd = ::open( name, O_RDONLY );
            io::error::throw_if( _fd == -1, "c-lib::open", errno, "failed to open file" );

            struct stat si;
            if ( ::fstat( _fd, &si ) < 0 )
            {
                auto err = errno;
                ::close( _fd );
                io::error::throw_if( false, "c-lib::fstat", err, "failed to get file size" );
            }

            _size = si.st_size;

            switch ( hint )
            {
            case cache_hint::none:
                _hint = MADV_NORMAL;
                break;
            case cache_hint::random:
                _hint = MADV_RANDOM;
                break;
            case cache_hint::sequential:
                _hint = MADV_SEQUENTIAL;
                break;
            }
        }

        ~mapped_file() noexcept
        {
            if ( _fd >= 0 )
                ::close( _fd );

            _fd   = -1;
            _size = 0;
        }

        size_t size() const { return _size; }

        mapped_view map_view( size_t offset, size_t size ) const
        {
            return mapped_view( _fd, offset, size, _hint );
        }

    private:
        int _hint;
        int _fd;
        size_t _size;
    };

}   // namespace sl::io
