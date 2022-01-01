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


#define C_ENG_MAP_START     CLASS ( Logger, PARENT ( Object ) )
#include <ObjectMapping.hpp>

Self * pActiveInstance = nullptr;

auto __setLoggerInstance ( // NOLINT(bugprone-reserved-identifier)
        Self * pInstance
) noexcept -> void {
    pActiveInstance = pInstance;
}

auto Self :: instance () noexcept (false) -> Self & {
    if ( pActiveInstance == nullptr ) {
        throw NullPointerException ( "Set a Logger Instance First" );
    }

    return * pActiveInstance;
}

auto Self :: currentTime () noexcept -> StringLiteral {
    static char timeBuffer [ Self :: defaultTimeBufferSize ];

    auto time = std :: chrono :: system_clock :: to_time_t ( std :: chrono :: system_clock :: now() );

    (void) std :: strftime ( // NOLINT(clion-misra-cpp2008-18-0-4)
            timeBuffer, Self :: defaultTimeBufferSize, // NOLINT(clion-misra-cpp2008-5-2-12)
            "%d-%m-%Y-%H:%M:%S",
            std :: localtime ( & time ) // NOLINT(clion-misra-cpp2008-18-0-4)
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
            "[time = %s][level = %s][engine state = %s] : %s",
            Self :: currentTime(),
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

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
            "{}";
}