//
// Created by loghin on 18.12.2021.
//

#include "Logger.hpp"

#include <CDS/Pointer>

#include <chrono>
#include <filesystem>
#include <fstream>

#include <Engine.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define __C_ENG_OBJECT_NAME Logger /* NOLINT(bugprone-reserved-identifier) */


auto __C_ENG_SELF :: instance () noexcept -> __C_ENG_SELF & {
    static __C_ENG_SELF instance;
    return instance;
}

auto __C_ENG_SELF :: currentTime () noexcept -> StringLiteral {
    static char timeBuffer [ __C_ENG_SELF :: defaultTimeBufferSize ];

    auto time = std :: chrono :: system_clock :: to_time_t ( std :: chrono :: system_clock :: now() );

    (void) std :: strftime ( // NOLINT(clion-misra-cpp2008-18-0-4)
            timeBuffer, __C_ENG_SELF :: defaultTimeBufferSize, // NOLINT(clion-misra-cpp2008-5-2-12)
            "%d-%m-%Y-%H:%M:%S",
            std :: localtime ( & time ) // NOLINT(clion-misra-cpp2008-18-0-4)
    );

    return timeBuffer;
}

__C_ENG_SELF :: __C_ENG_CONSTRUCTOR () noexcept {

#ifdef NDEBUG
    return;
#endif

    auto logsDirectory = "./logs"_s;
    String logFileName = logsDirectory + "/" + __C_ENG_SELF :: currentTime() + ".log";

    if ( ! std :: filesystem :: exists ( logsDirectory.cStr() ) ) {
        (void) std :: filesystem :: create_directory ( logsDirectory.toString().cStr() );
    }

    this->_outputBuffer = std :: fstream ( logFileName, std :: ios :: out | std :: ios :: trunc );
}

auto __C_ENG_SELF :: log (
        String                      const & message,
        __C_ENG_TYPE ( LogLevel )           logLevel
) noexcept -> __C_ENG_SELF & {

#ifdef NDEBUG
    return * this;
#endif

    if ( this->_logLevel < logLevel ) {
        return * this;
    }

    auto formattedMessage = String :: f (
            "[time = %s][level = %s][engine state = %s] : %s",
            __C_ENG_SELF :: currentTime(),
            :: toString ( logLevel ),
            :: toString ( __C_ENG_TYPE ( Engine ) :: instance().state() ),
            message.cStr()
    );

    this->_outputBuffer << formattedMessage << '\n';

    if ( this->_mirrorToConsole ) {
        std :: cout << formattedMessage << '\n';
    }

    return * this;
}

auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
            "{}";
}