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

#include <span>
#include <stdexcept>
#include <string>


export module sl.utils:strings;


namespace sl::utils
{

    export template< typename... Args >
    size_t calculate_string_length( const char* const format, Args... args )
    {
        auto length = std::snprintf( nullptr, 0, format, args... );
        if ( length <= 0 )
            throw std::runtime_error( "error computing format string length" );

        return length;
    }

    export template< typename... Args >
    size_t format_string( std::span< char > buffer, const char* const format, Args... args )
    {
        auto count = std::snprintf( buffer.data(), buffer.size(), format, args... );
        if ( count <= 0 )
            throw std::runtime_error( "error formatting string" );
        if ( static_cast< size_t >( count ) >= buffer.size() )
            throw std::runtime_error( "buffer too small" );

        return count + 1;   // NULL-terminated
    }

    export template< typename... Args >
    std::string format_string( const char* const format, Args... args )
    {
        auto needed = calculate_string_length( format, args... );
        auto str    = std::string( needed, 0 );
        auto buf    = std::span( &str[0], str.capacity() );

        format_string( buf, format, args... );

        return str;
    }

    export inline void replace_all( std::string& s, char search, char replace )
    {
        for ( auto& ch : s )
            if ( ch == search )
                ch = replace;
    }

    // Intentionally not a reference to force a copy and allocation.
    // We will convert the input argument in-place and return it.
    export std::string snake_to_pascal( std::string str )
    {
        bool cap = true;
        auto n   = 0;

        for ( unsigned char ch : str )
        {
            if ( ch == '_' )
            {
                cap = true;
                continue;
            }

            str[n++] = cap ? std::toupper( ch ) : ch;
            cap      = false;
        }

        str.resize( n );
        return str;
    }

}   // namespace sl::utils
