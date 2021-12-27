//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_LOGGER_HPP
#define __C_ENG_LOGGER_HPP


#include <Preprocess.hpp>

#include <CDS/Pointer>
#include <fstream>

#include <Core.hpp>

namespace engine {

    __C_ENG_CLASS ( Logger ) : public cds :: Object {
    public:
        
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( bool, defaultMirrorToConsole, false )                                                    // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( __C_ENG_TYPE ( LogLevel ), defaultLogLevel, __C_ENG_TYPE ( LogLevel ) :: LogLevelInfo )  // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint32, defaultTimeBufferSize, 256U )                                             // NOLINT(clion-misra-cpp2008-8-0-1)

    private:

        std :: fstream                          _outputBuffer;

        __C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( bool, mirrorToConsole, defaultMirrorToConsole )
        __C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( LogLevel ), logLevel, defaultLogLevel )

    public:

        __C_ENG_CONSTRUCTOR ( Logger ) () noexcept;

        static auto instance () noexcept -> __C_ENG_TYPE ( Logger ) &;
        static auto currentTime () noexcept -> cds :: StringLiteral;

        auto log ( cds :: String const &, __C_ENG_TYPE ( LogLevel ) ) noexcept -> __C_ENG_TYPE ( Logger ) &;

        inline auto forced ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelForced );
        }

        inline auto system ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelSystem );
        }

        inline auto fatal ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelFatal );
        }

        inline auto critical ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelCritical );
        }

        inline auto error ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelError );
        }

        inline auto warning ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelWarning );
        }

        inline auto debug ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelDebug );
        }

        inline auto info ( cds :: String const & message ) noexcept -> __C_ENG_TYPE ( Logger ) & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelInfo );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}


#endif //__C_ENG_LOGGER_HPP
