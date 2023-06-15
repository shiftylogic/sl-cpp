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

#include <mem/allocator.h>

#define FAKE_PTR reinterpret_cast< void* >( 0xDeadBeef )

TEST_CASE( "Raw alloc / free", "[utils][memory]" )
{
    size_t allocs   = 0;
    size_t reallocs = 0;
    size_t frees    = 0;

    auto alloc = [&allocs]( size_t size ) {
        allocs += 1;
        return FAKE_PTR;
    };
    auto realloc = [&reallocs]( void*, size_t ) -> void* {
        reallocs += 1;
        REQUIRE( false );
        return nullptr;
    };
    auto free = [&frees]( void* ptr ) {
        frees += 1;
        REQUIRE( ptr == FAKE_PTR );
    };

    {
        auto allocator = sl::mem::Allocator( { alloc, realloc, free } );

        auto ptr = allocator.Alloc( 1 );
        REQUIRE( ptr == FAKE_PTR );
        REQUIRE( allocs == 1 );
        REQUIRE( frees == 0 );

        allocator.Free( ptr );
        REQUIRE( allocs == 1 );
        REQUIRE( frees == 1 );
    }

    REQUIRE( allocs == 1 );
    REQUIRE( frees == 1 );
    REQUIRE( reallocs == 0 );
}

TEST_CASE( "Type alloc / free", "[utils][memory]" )
{
    auto alloc   = []( size_t size ) -> void* { return new unsigned char[size]; };
    auto realloc = []( void*, size_t ) {
        REQUIRE( false );
        return nullptr;
    };
    auto free = []( void* ptr ) { delete[] reinterpret_cast< unsigned char* >( ptr ); };

    static size_t ctorCalled = 0;
    static size_t dtorCalled = 0;

    struct Foo
    {
        Foo( int cookie )
            : _cookie( cookie )
        {
            ctorCalled += 1;
        }

        ~Foo() { dtorCalled += 1; }

        int Cookie() const { return _cookie; }

    private:
        int _cookie;
    };

    sl::mem::Allocator allocator( { alloc, realloc, free } );

    auto foo = allocator.AllocT< Foo >( 42 );
    REQUIRE( foo != nullptr );
    REQUIRE( ctorCalled == 1 );
    REQUIRE( dtorCalled == 0 );
    REQUIRE( foo->Cookie() == 42 );

    allocator.FreeT( foo );
    REQUIRE( ctorCalled == 1 );
    REQUIRE( dtorCalled == 1 );
}

TEST_CASE( "Type alloc w/ std::unique_ptr", "[utils][memory]" )
{
    auto alloc   = []( size_t size ) -> void* { return new unsigned char[size]; };
    auto realloc = []( void*, size_t ) {
        REQUIRE( false );
        return nullptr;
    };
    auto free = []( void* ptr ) { delete[] reinterpret_cast< unsigned char* >( ptr ); };

    static size_t ctorCalled = 0;
    static size_t dtorCalled = 0;

    struct Foo
    {
        Foo( int cookie )
            : _cookie( cookie )
        {
            ctorCalled += 1;
        }

        ~Foo() { dtorCalled += 1; }

        int Cookie() const { return _cookie; }

    private:
        int _cookie;
    };

    sl::mem::Allocator allocator( { alloc, realloc, free } );

    {
        auto foo = allocator.AllocSP< Foo >( 73 );
        REQUIRE( foo );
        REQUIRE( ctorCalled == 1 );
        REQUIRE( dtorCalled == 0 );
        REQUIRE( foo->Cookie() == 73 );
    }

    REQUIRE( ctorCalled == 1 );
    REQUIRE( dtorCalled == 1 );
}
