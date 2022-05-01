//
// Created by loghin on 18.12.2021.
//

#include "Logger.hpp"

#include <CDS/Pointer>

#include <threadIdentification/ThreadIdentification.hpp>

#include <chrono>
#include <filesystem>
#include <fstream>

#include <Engine.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( Logger, PARENT ( Object ) )
#include <ObjectMapping.hpp>

auto Self :: instance () noexcept -> Self & {
    static Self instance;
    return instance;
}

auto Self :: currentTime () noexcept -> StringLiteral {
    static char timeBuffer [ Self :: defaultTimeBufferSize ];
    static tm timeStruct;

    auto time = std :: chrono :: system_clock :: to_time_t ( std :: chrono :: system_clock :: now() );

#if defined(__CDS_Platform_Linux)
    localtime_r ( & time, & timeStruct );
#else
    localtime_s ( & timeStruct, & time );
#endif

    (void) std :: strftime ( // NOLINT(clion-misra-cpp2008-18-0-4)
            timeBuffer, Self :: defaultTimeBufferSize, // NOLINT(clion-misra-cpp2008-5-2-12)
            "%d-%m-%Y-%H:%M:%S",
            & timeStruct
    );

    return timeBuffer;
}

Self :: Constructor () noexcept {

#ifdef NDEBUG
    return;
#endif

    auto logsDirectory = "./logs"_s;
    String logFileName = logsDirectory + "/" + Self :: currentTime() + ".log";

    if ( ! std :: filesystem :: exists ( logsDirectory.cStr() ) ) {
        (void) std :: filesystem :: create_directory ( logsDirectory.toString().cStr() );
    }

    this->_outputBuffer = std :: fstream ( logFileName, std :: ios :: out | std :: ios :: trunc );
}

auto Self :: log (
        String                      const & message,
        __C_ENG_TYPE ( LogLevel )           logLevel
) noexcept -> Self & {

#ifdef NDEBUG
    return * this;
#endif

    if ( this->_logLevel < logLevel ) {
        return * this;
    }

    auto formattedMessage = String :: f (
            "[time = %s][level = %s][engine state = %s][thread = %s] : %s",
            Self :: currentTime(),
            :: toString ( logLevel ),
            :: toString ( __C_ENG_TYPE ( Engine ) :: instance().state() ),
            getThreadIdentificationString ( Thread :: currentThreadID() ),
            message.cStr()
    );

    this->_outputBuffer << formattedMessage << '\n';

    if ( this->_mirrorToConsole ) {
        std :: cout << formattedMessage << '\n';
    }

    return * this;
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
            "{}";
}