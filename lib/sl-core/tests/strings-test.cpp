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

#include <utils/strings.h>

TEST_CASE( "Formatted lengths", "[utils][strings]" )
{
    auto count = sl::utils::CalculateFormattedLength( "something: %s - with <%i>", "dude", 12387 );
    REQUIRE( count == strlen( "something: dude - with <12387>" ) );
}

TEST_CASE( "String formatting (non-allocating)", "[utils][strings]" )
{
    std::string expected( "Int: 42, String: test" );
    std::array< char, 256 > buffer;

    auto count = sl::utils::FormatString( buffer, "Int: %d, String: %s", 42, "test" );
    REQUIRE( count == expected.size() + 1 );
    REQUIRE( buffer[count - 1] == 0 );
    REQUIRE( std::string( buffer.data(), count - 1 ) == expected );
}

TEST_CASE( "String formatting (allocating)", "[utils][strings]" )
{
    std::string expected( "This string contains a string (a string) and a float (1.123)." );

    auto actual = sl::utils::FormatString(
        "This string contains a string (%s) and a float (%1.3f).", "a string", 1.123f );
    REQUIRE( actual.size() == expected.size() );
    REQUIRE( actual == expected );
}

TEST_CASE( "String replace all matching chars", "[utils][strings]" )
{
    std::string str = "aabbbbabaabaaacdd999sdf98";

    sl::utils::ReplaceAll( str, 's', '+' );
    REQUIRE( str == "aabbbbabaabaaacdd999+df98" );

    sl::utils::ReplaceAll( str, '8', '+' );
    REQUIRE( str == "aabbbbabaabaaacdd999+df9+" );

    sl::utils::ReplaceAll( str, 'b', '+' );
    REQUIRE( str == "aa++++a+aa+aaacdd999+df9+" );

    sl::utils::ReplaceAll( str, 'f', '+' );
    REQUIRE( str == "aa++++a+aa+aaacdd999+d+9+" );

    sl::utils::ReplaceAll( str, '9', '+' );
    REQUIRE( str == "aa++++a+aa+aaacdd++++d+++" );

    sl::utils::ReplaceAll( str, 'a', '+' );
    REQUIRE( str == "++++++++++++++cdd++++d+++" );

    sl::utils::ReplaceAll( str, 'd', '+' );
    REQUIRE( str == "++++++++++++++c++++++++++" );

    sl::utils::ReplaceAll( str, 'c', '+' );
    REQUIRE( str == "+++++++++++++++++++++++++" );

    sl::utils::ReplaceAll( str, '+', '0' );
    REQUIRE( str == "0000000000000000000000000" );
}

TEST_CASE( "String snake to pascal", "[utils][strings]" )
{
    // Make sure it is not in-place
    std::string str = "test_the_thing";
    auto res        = sl::utils::SnakeToPascal( str );
    REQUIRE( res == "TestTheThing" );
    REQUIRE( res.size() == 12 );
    REQUIRE( str == "test_the_thing" );

    // Now, just a bunch of different variations.
    REQUIRE( sl::utils::SnakeToPascal( "" ) == "" );
    REQUIRE( sl::utils::SnakeToPascal( "_" ) == "" );
    REQUIRE( sl::utils::SnakeToPascal( "a" ) == "A" );
    REQUIRE( sl::utils::SnakeToPascal( "B" ) == "B" );
    REQUIRE( sl::utils::SnakeToPascal( "Ba" ) == "Ba" );
    REQUIRE( sl::utils::SnakeToPascal( "ba" ) == "Ba" );
    REQUIRE( sl::utils::SnakeToPascal( "bA" ) == "BA" );
    REQUIRE( sl::utils::SnakeToPascal( "aaa_bbbbb_c" ) == "AaaBbbbbC" );
    REQUIRE( sl::utils::SnakeToPascal( "_a_bbbbb_c" ) == "ABbbbbC" );
    REQUIRE( sl::utils::SnakeToPascal( "_a_bbbBb_c" ) == "ABbbBbC" );
    REQUIRE( sl::utils::SnakeToPascal( "_a_bbbbb_" ) == "ABbbbb" );
}
