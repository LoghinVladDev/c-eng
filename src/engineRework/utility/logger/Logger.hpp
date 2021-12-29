//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_LOGGER_HPP
#define __C_ENG_LOGGER_HPP


#include <Preprocess.hpp>

#include <CDS/Pointer>
#include <fstream>

#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( Logger, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( bool, defaultMirrorToConsole, false )                                                    // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( __C_ENG_TYPE ( LogLevel ), defaultLogLevel, __C_ENG_TYPE ( LogLevel ) :: LogLevelInfo )  // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: uint32, defaultTimeBufferSize, 256U )                                             // NOLINT(clion-misra-cpp2008-8-0-1)

    private:

        std :: fstream                          _outputBuffer;

        __C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( bool, mirrorToConsole, defaultMirrorToConsole )
        __C_ENG_CLASS_MUTABLE_PRIMITIVE_FIELD ( __C_ENG_TYPE ( LogLevel ), logLevel, defaultLogLevel )

    public:

        Constructor () noexcept;

        static auto instance () noexcept -> Self &;
        static auto currentTime () noexcept -> cds :: StringLiteral;

        auto log ( cds :: String const &, __C_ENG_TYPE ( LogLevel ) ) noexcept -> Self &;

        inline auto forced ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelForced );
        }

        inline auto system ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelSystem );
        }

        inline auto fatal ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelFatal );
        }

        inline auto critical ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelCritical );
        }

        inline auto error ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelError );
        }

        inline auto warning ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelWarning );
        }

        inline auto debug ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelDebug );
        }

        inline auto info ( cds :: String const & message ) noexcept -> Self & {
            return this->log ( message, __C_ENG_TYPE ( LogLevel ) :: LogLevelInfo );
        }

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_LOGGER_HPP
