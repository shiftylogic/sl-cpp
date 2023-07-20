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

#include <stdexcept>
#include <string>


export module sl.io:error;

import sl.utils;


namespace sl::io
{

    export class error : public std::runtime_error
    {
    public:
        error( const char* api, int code, const char* message )
            : std::runtime_error { io::error::make_message( api, code, message ) }
        {}

        static void
        throw_if( bool condition, const char* api, int code, const char* message = nullptr )
        {
            if ( condition )
                throw io::error { api, code, message };
        }

    private:
        static std::string make_message( const char* api, int code, const char* message )
        {
            const char* msg = ( nullptr == message ) ? "<unspecified>" : message;
            return sl::utils::format_string( "IO Error (%s): [%d] %s", api, code, msg );
        }
    };

}   // namespace sl::io
