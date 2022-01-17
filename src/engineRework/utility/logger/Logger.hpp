//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_LOGGER_HPP__
#define __C_ENG_LOGGER_HPP__


#include <Preprocess.hpp>

#include <CDS/Pointer>
#include <fstream>

#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( Logger, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        Const ( PRIMITIVE_TYPE ( bool ),            defaultMirrorToConsole, VALUE ( false ) )
        Const ( ENGINE_PRIMITIVE_TYPE ( LogLevel ), defaultLogLevel,        VALUE ( LogLevelInfo ) )
        Const ( PRIMITIVE_TYPE ( cds :: uint32 ),   defaultTimeBufferSize,  VALUE ( 256 ) )

        Field ( TYPE ( std :: fstream ),                outputBuffer,       NO_INIT,                                    GET_NONE,       SET_NONE )
        Field ( PRIMITIVE_TYPE ( bool ),                mirrorToConsole,    DEFAULT_VALUE ( defaultMirrorToConsole ),   GET_DEFAULT,    SET_DEFAULT )
        Field ( ENGINE_PRIMITIVE_TYPE ( LogLevel ),     logLevel,           DEFAULT_VALUE ( defaultLogLevel ),          GET_DEFAULT,    SET_DEFAULT )

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


#endif //__C_ENG_LOGGER_HPP__
