//
// Created by loghin on 18.12.2021.
//

#ifndef C_ENG_LOGGER_HPP
#define C_ENG_LOGGER_HPP


#include <Preprocess.hpp>

#include <CDS/Pointer>
#include <fstream>

#include <Core.hpp>

namespace engine {

    class C_ENG_CLASS ( Logger ) : public cds :: Object {
    public:
        
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( bool, defaultMirrorToConsole, false )                  // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( LogLevel, defaultLogLevel, LogLevel :: LogLevelInfo )  // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint32, defaultTimeBufferSize, 256U )           // NOLINT(clion-misra-cpp2008-8-0-1)

    private:

        std :: fstream                          _outputBuffer;

        C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( bool, mirrorToConsole, defaultMirrorToConsole )
        C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( LogLevel, logLevel, defaultLogLevel )

    public:

        C_ENG_CONSTRUCTOR ( Logger ) () noexcept;

        static auto instance () noexcept -> C_ENG_TYPE ( Logger ) &;
        static auto currentTime () noexcept -> cds :: StringLiteral;

        auto log ( cds :: String const &, LogLevel ) noexcept -> C_ENG_TYPE ( Logger ) &;

        inline auto forced ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelForced );
        }

        inline auto system ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelSystem );
        }

        inline auto fatal ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelFatal );
        }

        inline auto critical ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelCritical );
        }

        inline auto error ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelError );
        }

        inline auto warning ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelWarning );
        }

        inline auto debug ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelDebug );
        }

        inline auto info ( cds :: String const & message ) noexcept -> C_ENG_TYPE ( Logger ) & {
            return this->log ( message, LogLevel :: LogLevelInfo );
        }

    };

}

#endif //C_ENG_LOGGER_HPP
