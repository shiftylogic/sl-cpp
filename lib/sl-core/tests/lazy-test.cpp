/**
 * MIT License
 *
 * Copyright (c) 2023 Robert Anderson
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

#include <catch2/catch.hpp>

#include <utils/lazy.h>

TEST_CASE( "Lazy no args", "[utils]" )
{
    static size_t ctorCalled = 0;
    static size_t dtorCalled = 0;

    struct Thing
    {
        Thing() { ctorCalled += 1; }
        ~Thing() { dtorCalled += 1; }
    };

    {
        sl::utils::Lazy< Thing > thing;
        REQUIRE( ctorCalled == 0 );
        REQUIRE( dtorCalled == 0 );

        thing.Get();
        REQUIRE( ctorCalled == 1 );
        REQUIRE( dtorCalled == 0 );
    }

    REQUIRE( ctorCalled == 1 );
    REQUIRE( dtorCalled == 1 );
}

TEST_CASE( "Lazy w/ args", "[utils]" )
{
    static size_t ctorCalled = 0;
    static size_t dtorCalled = 0;

    struct Thing
    {
        Thing( int cookie1, std::string cookie2 )
            : _cookie1( cookie1 )
            , _cookie2( cookie2 )
        {
            ctorCalled += 1;
        }

        ~Thing() { dtorCalled += 1; }

        int Cookie1() const { return _cookie1; }
        std::string Cookie2() const { return _cookie2; }

    private:
        int _cookie1;
        std::string _cookie2;
    };

    {
        sl::utils::Lazy< Thing, int, std::string > thing( 42, "dude" );
        REQUIRE( ctorCalled == 0 );
        REQUIRE( dtorCalled == 0 );

        auto& t = thing.Get();
        REQUIRE( ctorCalled == 1 );
        REQUIRE( dtorCalled == 0 );

        auto& t2 = thing.Get();
        REQUIRE( &t == &t2 );
        REQUIRE( t.Cookie1() == 42 );
        REQUIRE( t.Cookie2() == "dude" );
    }

    REQUIRE( ctorCalled == 1 );
    REQUIRE( dtorCalled == 1 );
}
