//
// Created by loghin on 18.12.2021.
//

#ifndef __C_ENG_LOGGER_HPP__
#define __C_ENG_LOGGER_HPP__ /* NOLINT(bugprone-reserved-identifier) */


#include <Preprocess.hpp>

#include <CDS/Pointer>
#include <fstream>

#include <Core.hpp>


#define C_ENG_MAP_START     CLASS ( Logger, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
        /**
         * Logger class extras:
         *      - log regex match : ^\[time\s*=\s([^\]]*)\]\[level\s*=\s*([\w]*)\]\[engine state\s*=\s*([\w\s]*)\]\s*:\s*(.+)$
         *
         *      levels :
         *          ^\s*f(orced)?\s*$       -   LogHighlightingPattern(enabled=true, pattern=^\s*f(orced)?\s*$, action=HIGHLIGHT_LINE, fgRgb=-393219, bgRgb=-65523, bold=true, italic=false, showOnStripe=true)
         *          ^\s*s(ystem)?\s*$       -   LogHighlightingPattern(enabled=true, pattern=^\s*s(ystem)?\s*$, action=HIGHLIGHT_LINE, fgRgb=-13701, bgRgb=null, bold=true, italic=false, showOnStripe=false)
         *          ^\s*fa(tal)?\s*$        -   LogHighlightingPattern(enabled=true, pattern=^\s*fa(tal)?\s*$, action=HIGHLIGHT_LINE, fgRgb=-65524, bgRgb=null, bold=true, italic=false, showOnStripe=true)
         *          ^\s*c(ritical)?\s*$     -   LogHighlightingPattern(enabled=true, pattern=^\s*c(ritical)?\s*$, action=HIGHLIGHT_FIELD, fgRgb=-65535, bgRgb=null, bold=false, italic=false, showOnStripe=true)
         *          ^\s*e(rror)?\s*$        -   LogHighlightingPattern(enabled=true, pattern=^\s*e(rror)?\s*$, action=HIGHLIGHT_FIELD, fgRgb=-39680, bgRgb=null, bold=false, italic=false, showOnStripe=true)
         *          ^\s*w(arn(ing)?)?\s*$   -   LogHighlightingPattern(enabled=true, pattern=^\s*w(arn(ing)?)?\s*$, action=HIGHLIGHT_FIELD, fgRgb=-8960, bgRgb=null, bold=false, italic=false, showOnStripe=true)
         *          ^\s*d(ebug)?\s*$        -   LogHighlightingPattern(enabled=true, pattern=^\s*d(ebug)?\s*$, action=HIGHLIGHT_LINE, fgRgb=-6030593, bgRgb=null, bold=false, italic=true, showOnStripe=false)
         *          ^\s*i(nfo)?\s*$         -   LogHighlightingPattern(enabled=true, pattern=^\s*i(nfo)?\s*$, action=HIGHLIGHT_FIELD, fgRgb=-8454289, bgRgb=null, bold=false, italic=false, showOnStripe=false)
         *
         */

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


#include <sstream>
#define C_ENG_MAP_START CLASS ( LogStream,  PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
        namespace impl {
            Class {
                Field ( ENGINE_PRIMITIVE_TYPE ( LogLevel const ),   logLevel,   NO_INIT,                GET_NONE,   SET_NONE );
                Field ( TYPE ( std :: ostringstream ),              stream,     NO_INIT,                GET_NONE,   SET_NONE );
                Field ( PRIMITIVE_TYPE ( bool ),                    moved,      DEFAULT_VALUE (false),  GET_NONE,   SET_NONE );

            public:
                explicit Constructor ( Type ( LogLevel ) level ) noexcept :
                        _logLevel ( level ) {

                }

                Constructor ( Self && obj ) noexcept :
                        _logLevel ( obj._logLevel ),
                        _stream ( std :: move ( obj._stream ) ) {

                    obj._moved = true;
                }

                Destructor () noexcept {

                    if ( ! this->_moved ) {
                        (void) Type ( Logger ) :: instance().log ( this->_stream.str(), this->_logLevel );
                    }
                }

                template < typename T >
                inline auto operator << ( T const & obj ) && noexcept -> Self {

                    this->_stream << obj;
                    return std :: move ( * this );
                }
            };
        }
    }

    namespace log {
        inline auto info () noexcept -> hidden :: impl :: Self {
            return hidden :: impl :: Self ( LogLevelInfo );
        }

        inline auto warn () noexcept -> hidden :: impl :: Self {
            return hidden :: impl :: Self ( LogLevelWarning );
        }

        inline auto err () noexcept -> hidden :: impl :: Self {
            return hidden :: impl :: Self ( LogLevelError );
        }

        inline auto sys () noexcept -> hidden :: impl :: Self {
            return hidden :: impl :: Self ( LogLevelSystem );
        }
    }
}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_LOGGER_HPP__
