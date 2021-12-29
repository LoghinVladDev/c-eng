//
// Created by loghin on 19.12.2021.
//

#ifndef __C_ENG_SETTINGS_HPP
#define __C_ENG_SETTINGS_HPP

#include <Preprocess.hpp>
#include <CDS/HashMap>


#define C_ENG_MAP_START     CLASS ( Settings, EXTERNAL_PARENT ( cds :: Object ) )
#include <ObjectMapping.hpp>

namespace engine {

    Class {
    public:
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: StringLiteral, defaultPath, "./settings.cfg" ); // NOLINT(clion-misra-cpp2008-8-0-1)

        using Key = cds :: StringLiteral;
        using Value = cds :: uint64;

        /// engine settings
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyUseValidationLayers, "validationLayersEnabled" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultUseValidationLayers, 1ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyLogToConsole, "logToConsole" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultLogToConsole, 1ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        /// engine game object settings
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyPeriodicCacheReconstructionInterval, "periodicCacheReconstructionInterval" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultPeriodicCacheReconstructionInterval, 2048ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        /// window settings
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyMouseCursorEnabled, "mouseCursorEnabled" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultMouseCursorEnabled, 1ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyShowFramesPerSecond, "showFPS" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultShowFramesPerSecond, 0ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyResolution, "resolution" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultResolution, ( 1366ull << 32 ) | ( 768ull ) ) // NOLINT(clion-misra-cpp2008-8-0-1)

        /// render settings
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyFieldOfView, "fieldOfView" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultFieldOfView, 90ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyDrawDistance, "drawDistance" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        __C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultDrawDistance, 200ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

    private:
        cds :: HashMap < cds :: String, Value >       _settings;

        Constructor () noexcept = default;

        __C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool, initialized, false )

        auto load () noexcept -> Self &;
        auto save () noexcept -> Self &;

    public:
        Destructor () noexcept;

        static auto instance () noexcept -> Self &;

        auto get ( Key ) noexcept -> Value;
        auto set ( Key, Value ) noexcept -> Self &;

        static auto defaultForKey ( Key ) noexcept -> Value;

        __C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#define C_ENG_MAP_END
#include <ObjectMapping.hpp>


#endif //__C_ENG_SETTINGS_HPP
