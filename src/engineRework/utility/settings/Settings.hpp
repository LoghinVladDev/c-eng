//
// Created by loghin on 19.12.2021.
//

#ifndef C_ENG_SETTINGS_HPP
#define C_ENG_SETTINGS_HPP

#include <Preprocess.hpp>
#include <CDS/HashMap>

namespace engine {

    class C_ENG_CLASS ( Settings ) : public cds :: Object {
    public:
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( cds :: StringLiteral, defaultPath, "./settings.cfg" ); // NOLINT(clion-misra-cpp2008-8-0-1)

        using Key = cds :: StringLiteral;
        using Value = cds :: uint64;

        /// engine settings
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyUseValidationLayers, "validationLayersEnabled" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultUseValidationLayers, 1ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyLogToConsole, "logToConsole" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultLogToConsole, 1ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        /// engine game object settings
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyPeriodicCacheReconstructionInterval, "periodicCacheReconstructionInterval" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultPeriodicCacheReconstructionInterval, 2048ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        /// window settings
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyMouseCursorEnabled, "mouseCursorEnabled" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultMouseCursorEnabled, 1ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyShowFramesPerSecond, "showFPS" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultShowFramesPerSecond, 0ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyResolution, "resolution" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultResolution, ( 1366ull << 32 ) | ( 768ull ) ) // NOLINT(clion-misra-cpp2008-8-0-1)

        /// render settings
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyFieldOfView, "fieldOfView" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultFieldOfView, 90ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Key, keyDrawDistance, "drawDistance" ) // NOLINT(clion-misra-cpp2008-8-0-1)
        C_ENG_CLASS_PRIMITIVE_CONSTANT ( Value, defaultDrawDistance, 200ull ) // NOLINT(clion-misra-cpp2008-8-0-1)

    private:
        cds :: HashMap < cds :: String, Value >       _settings;

        C_ENG_CONSTRUCTOR ( Settings ) () noexcept = default;

        C_ENG_CLASS_IMMUTABLE_PRIMITIVE_FIELD ( bool, initialized, false )

        auto load () noexcept -> C_ENG_TYPE ( Settings ) &;
        auto save () noexcept -> C_ENG_TYPE ( Settings ) &;

    public:
        C_ENG_DESTRUCTOR ( Settings ) () noexcept;

        static auto instance () noexcept -> C_ENG_TYPE ( Settings ) &;

        auto get ( Key ) noexcept -> Value;
        auto set ( Key, Value ) noexcept -> C_ENG_TYPE ( Settings ) &;

        static auto defaultForKey ( Key ) noexcept -> Value;

        C_ENG_NO_DISCARD auto toString () const noexcept -> cds :: String override;
    };

}

#endif //C_ENG_SETTINGS_HPP
