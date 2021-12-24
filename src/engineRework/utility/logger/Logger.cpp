//
// Created by loghin on 18.12.2021.
//

#include "Logger.hpp"

#include <CDS/Pointer>

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( Logger ) :: instance () noexcept -> C_ENG_TYPE ( Logger ) & {
    static C_ENG_TYPE ( Logger ) instance;
    return instance;
}

#include <chrono>
auto C_ENG_CLASS ( Logger ) :: currentTime () noexcept -> StringLiteral {
    static char timeBuffer [ C_ENG_CLASS ( Logger ) :: defaultTimeBufferSize ];

    auto time = std :: chrono :: system_clock :: to_time_t ( std :: chrono :: system_clock :: now() );

    (void) std :: strftime ( // NOLINT(clion-misra-cpp2008-18-0-4)
            timeBuffer, C_ENG_CLASS ( Logger ) :: defaultTimeBufferSize, // NOLINT(clion-misra-cpp2008-5-2-12)
            "%d-%m-%Y-%H:%M:%S",
            std :: localtime ( & time ) // NOLINT(clion-misra-cpp2008-18-0-4)
    );

    return timeBuffer;
}

#include <filesystem>
#include <fstream>

C_ENG_CLASS ( Logger ) :: C_ENG_CONSTRUCTOR ( Logger ) () noexcept {

#ifdef NDEBUG
    return;
#endif

    auto logsDirectory = "./logs"_s;
    String logFileName = logsDirectory + "/" + C_ENG_CLASS ( Logger ) :: currentTime() + ".log";

    if ( ! std :: filesystem :: exists ( logsDirectory.cStr() ) ) {
        (void) std :: filesystem :: create_directory ( logsDirectory.toString().cStr() );
    }

    this->_outputBuffer = std :: fstream ( logFileName, std :: ios :: out | std :: ios :: trunc );
}

#include <Engine.hpp>

auto C_ENG_CLASS ( Logger ) :: log (
        String  const & message,
        LogLevel        logLevel
) noexcept -> C_ENG_TYPE ( Logger ) & {

#ifdef NDEBUG
    return * this;
#endif

    if ( this->_logLevel < logLevel ) {
        return * this;
    }

    auto formattedMessage = String :: f (
            "[time = %s][level = %s][engine state = %s] : %s",
            C_ENG_CLASS ( Logger ) :: currentTime(),
            :: toString ( logLevel ),
            :: toString ( C_ENG_CLASS ( Engine :: instance().state() ) ),
            message.cStr()
    );

    this->_outputBuffer << formattedMessage << '\n';

    if ( this->_mirrorToConsole ) {
        std :: cout << formattedMessage << '\n';
    }

    return * this;
}

auto C_ENG_CLASS ( Logger ) :: toString () const noexcept -> String {
    return "Logger {}";
}