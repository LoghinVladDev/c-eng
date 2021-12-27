//
// Created by loghin on 19.12.2021.
//

#include "Settings.hpp"

#include <Logger.hpp>

#include <CDS/Path>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Settings /* NOLINT(bugprone-reserved-identifier) */


auto __C_ENG_SELF :: instance () noexcept -> __C_ENG_SELF & {
    static __C_ENG_SELF settings;

    if ( ! settings.initialized() ) {
        (void) settings.load();
    }

    return settings;
}

auto __C_ENG_SELF :: load () noexcept -> __C_ENG_SELF & {

    (void) __C_ENG_TYPE ( Logger ) :: instance().info ( "Initializing Settings" );

    try {
        Path path ( defaultPath );

        std :: fstream configFile ( path.toString(), std :: ios :: in );
        std :: string line;

        while ( std :: getline ( configFile, line ) ) {
            auto pair = String ( line ).split("=");

            this->_settings [ pair[0] ] = static_cast < uint64 > ( Long :: parse ( pair[1] ) );
        }

        (void) __C_ENG_TYPE ( Logger ) :: instance ().debug ( "Settings initialized from file at " + path.toString() );

    } catch ( Exception const & ) {

        (void) __C_ENG_TYPE ( Logger ) :: instance ().debug ( "Settings initialization failed, no file present. Commencing with defaults" );

    }

    this->_initialized = true;

    return * this;
}

auto __C_ENG_SELF :: get ( Key key ) noexcept -> Value {
    if ( ! this->_settings.containsKey ( key ) ) {
        this->_settings [ String ( key ) ] = __C_ENG_SELF :: defaultForKey ( key );
    }

    return this->_settings [ String ( key ) ];
}

auto __C_ENG_SELF :: set ( Key key, Value value ) noexcept -> __C_ENG_SELF & {
    this->_settings [ String (key) ] = value;

    return * this;
}

static HashMap < String, __C_ENG_SELF :: Value > defaults = {
        { __C_ENG_TYPE ( Settings ) :: keyUseValidationLayers,                   __C_ENG_TYPE ( Settings ) :: defaultUseValidationLayers },
        { __C_ENG_TYPE ( Settings ) :: keyLogToConsole,                          __C_ENG_TYPE ( Settings ) :: defaultLogToConsole },
        { __C_ENG_TYPE ( Settings ) :: keyPeriodicCacheReconstructionInterval,   __C_ENG_TYPE ( Settings ) :: defaultPeriodicCacheReconstructionInterval },
        { __C_ENG_TYPE ( Settings ) :: keyMouseCursorEnabled,                    __C_ENG_TYPE ( Settings ) :: defaultMouseCursorEnabled },
        { __C_ENG_TYPE ( Settings ) :: keyShowFramesPerSecond,                   __C_ENG_TYPE ( Settings ) :: defaultShowFramesPerSecond },
        { __C_ENG_TYPE ( Settings ) :: keyResolution,                            __C_ENG_TYPE ( Settings ) :: defaultResolution },
        { __C_ENG_TYPE ( Settings ) :: keyFieldOfView,                           __C_ENG_TYPE ( Settings ) :: defaultFieldOfView },
        { __C_ENG_TYPE ( Settings ) :: keyDrawDistance,                          __C_ENG_TYPE ( Settings ) :: defaultDrawDistance }
};

auto __C_ENG_SELF :: defaultForKey ( Key key ) noexcept -> Value {
    if ( defaults.containsKey ( String ( key ) ) ) {
        return defaults [ String ( key ) ];
    }

    return 0ULL;
}

__C_ENG_SELF :: __C_ENG_DESTRUCTOR () noexcept {
    (void) this->save();
}

auto __C_ENG_SELF :: save () noexcept -> __C_ENG_SELF & {
    std :: fstream file ( defaultPath, std :: ios :: out | std :: ios :: trunc );

    for ( auto & pair : this->_settings ) {
        file << pair.first() << '=' << pair.second() << '\n';
    }

    return * this;
}

auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
           "{ initialized = "_s + :: toString ( this->initialized() ) +
           ", settings = "      + this->_settings.toString();
}