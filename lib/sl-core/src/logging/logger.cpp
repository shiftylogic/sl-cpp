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

#include <array>
#include <fstream>
#include <iostream>


export module sl.logging:logger;

import sl.utils;


namespace sl::logging
{

    constexpr size_t kMaxLogLine = 512;

    enum class Level
    {
        Fatal,
        Error,
        Warning,
        Info,
        Trace,
    };

    export class Logger
    {
    public:
        Logger( const Logger& )            = delete;
        Logger( Logger&& )                 = delete;
        Logger& operator=( const Logger& ) = delete;
        Logger&& operator=( Logger&& )     = delete;

        Logger()
            : _log( std::cout )
        {}

        explicit Logger( const char* logFile )
            : _fLog( logFile, std::ios::app )
            , _log( _fLog )
        {}

        void Log( Level level, const char* msg )
        {
            const std::array< const char*, 5 > levels {
                "FATAL", "ERROR", "WARNING", "INFO", "TRACE" };

            _log << "[" << levels[static_cast< int >( level )] << "] " << msg << "\n";
            _log.flush();
        }

        template< typename... Args >
        void Log( Level level, const char* format, Args... args )
        {
            std::array< char, kMaxLogLine > buf;

            auto count = std::snprintf( buf.data(), buf.size(), format, args... );
            if ( count <= 0 )
                throw std::runtime_error( "error formatting log string" );

            Log( level, buf.data() );
        }

        template< typename... Args >
        void Fatal( const char* format, Args... args )
        {
            Log( Level::Fatal, format, std::forward< Args >( args )... );
        }

        template< typename... Args >
        void Error( const char* format, Args... args )
        {
            Log( Level::Error, format, std::forward< Args >( args )... );
        }

        template< typename... Args >
        void Warn( const char* format, Args... args )
        {
            Log( Level::Warning, format, std::forward< Args >( args )... );
        }

        template< typename... Args >
        void Info( const char* format, Args... args )
        {
            Log( Level::Info, format, std::forward< Args >( args )... );
        }

        template< typename... Args >
        void Trace( const char* format, Args... args )
        {
            Log( Level::Trace, format, std::forward< Args >( args )... );
        }

    private:
        std::ofstream _fLog;
        std::ostream& _log;
    };

}   // namespace sl::logging
