//
// Created by loghin on 19.12.2021.
//

#ifndef __C_ENG_SETTINGS_HPP__
#define __C_ENG_SETTINGS_HPP__

#include <Preprocess.hpp>
#include <CDS/HashMap>


#define C_ENG_MAP_START     CLASS ( Settings, PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        using Key = cds :: StringLiteral;
        using Value = cds :: uint64;

        Const ( PRIMITIVE_TYPE ( cds :: StringLiteral ),    defaultPath,                                VALUE ( "./settings.cfg" ) )

        /// engine settings
        Const ( PRIMITIVE_TYPE ( Key ),                     keyUseValidationLayers,                     VALUE ( "validationLayersEnabled" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultUseValidationLayers,                 VALUE ( 1ull ) )

        Const ( PRIMITIVE_TYPE ( Key ),                     keyLogToConsole,                            VALUE ( "logToConsole" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultLogToConsole,                        VALUE ( 1ull ) )

        /// engine game object settings
        Const ( PRIMITIVE_TYPE ( Key ),                     keyPeriodicCacheReconstructionInterval,     VALUE ( "periodicCacheReconstructionInterval" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultPeriodicCacheReconstructionInterval, VALUE ( 2048ull ) )

        /// window settings
        Const ( PRIMITIVE_TYPE ( Key ),                     keyMouseCursorEnabled,                      VALUE ( "mouseCursorEnabled" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultMouseCursorEnabled,                  VALUE ( 1ull ) )

        Const ( PRIMITIVE_TYPE ( Key ),                     keyShowFramesPerSecond,                     VALUE ( "showFPS" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultShowFramesPerSecond,                 VALUE ( 0ull ) )

        Const ( PRIMITIVE_TYPE ( Key ),                     keyResolution,                              VALUE ( "resolution" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultResolution,                          VALUE ( ( 1366ull << 32 ) | ( 768ull ) ) )  // NOLINT(clion-misra-cpp2008-5-8-1)

        /// render settings
        Const ( PRIMITIVE_TYPE ( Key ),                     keyFieldOfView,                             VALUE ( "fieldOfView" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultFieldOfView,                         VALUE ( 90ull ) )

        Const ( PRIMITIVE_TYPE ( Key ),                     keyDrawDistance,                            VALUE ( "drawDistance" ) )
        Const ( PRIMITIVE_TYPE ( Value ),                   defaultDrawDistance,                        VALUE ( 200ull ) )

    private:
        Field ( TYPE ( cds :: HashMap < cds :: String, Value > ),   settings,       NO_INIT,                    GET_NONE,       SET_NONE )
        Field ( PRIMITIVE_TYPE ( bool ),                            initialized,    DEFAULT_VALUE ( false ),    GET_DEFAULT,    SET_NONE )

        Constructor () noexcept = default;

        auto load () noexcept -> Self &;
        auto save () noexcept -> Self &;

    public:
        Destructor () noexcept;

        static auto instance () noexcept -> Self &;

        __C_ENG_NO_DISCARD auto get ( Key ) noexcept -> Value;
        __C_ENG_NO_DISCARD inline auto get ( cds :: String const & key ) noexcept -> Value {
            return this->get(key.cStr());
        }

        auto set ( Key, Value ) noexcept -> Self &;

        static auto defaultForKey ( Key ) noexcept -> Value;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_SETTINGS_HPP__
