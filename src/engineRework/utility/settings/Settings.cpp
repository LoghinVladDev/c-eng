//
// Created by loghin on 19.12.2021.
//

#include "Settings.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Logger.hpp>

auto C_ENG_CLASS ( Settings ) :: instance () noexcept -> C_ENG_TYPE ( Settings ) & {
    static C_ENG_TYPE ( Settings ) settings;

    if ( ! settings.initialized() ) {
        (void) settings.load();
    }

    return settings;
}

#include <CDS/Path>

auto C_ENG_CLASS ( Settings ) :: load () noexcept -> C_ENG_TYPE ( Settings ) & {

    (void) C_ENG_CLASS ( Logger ) :: instance().info ( "Initializing Settings" );

    try {
        Path path ( defaultPath );

        std :: fstream configFile ( path.toString(), std :: ios :: in );
        std :: string line;

        while ( std :: getline ( configFile, line ) ) {
            auto pair = String ( line ).split("=");

            this->_settings [ pair[0] ] = static_cast < uint64 > ( Long :: parse ( pair[1] ) );
        }

        (void) C_ENG_CLASS ( Logger ) :: instance ().debug ( "Settings initialized from file at " + path.toString() );

    } catch ( Exception const & ) {

        (void) C_ENG_CLASS ( Logger ) :: instance ().debug ( "Settings initialization failed, no file present. Commencing with defaults" );

    }

    this->_initialized = true;

    return * this;
}

auto C_ENG_CLASS ( Settings ) :: get ( Key key ) noexcept -> Value {
    if ( ! this->_settings.containsKey ( key ) ) {
        this->_settings [ String ( key ) ] = C_ENG_CLASS ( Settings ) :: defaultForKey ( key );
    }

    return this->_settings [ String ( key ) ];
}

auto C_ENG_CLASS ( Settings ) :: set ( Key key, Value value ) noexcept -> C_ENG_TYPE ( Settings ) & {
    this->_settings [ String (key) ] = value;

    return * this;
}

static HashMap < String, C_ENG_CLASS ( Settings ) :: Value > defaults = {
        { C_ENG_CLASS ( Settings ) :: keyUseValidationLayers,                   C_ENG_CLASS ( Settings ) :: defaultUseValidationLayers },
        { C_ENG_CLASS ( Settings ) :: keyLogToConsole,                          C_ENG_CLASS ( Settings ) :: defaultLogToConsole },
        { C_ENG_CLASS ( Settings ) :: keyPeriodicCacheReconstructionInterval,   C_ENG_CLASS ( Settings ) :: defaultPeriodicCacheReconstructionInterval },
        { C_ENG_CLASS ( Settings ) :: keyMouseCursorEnabled,                    C_ENG_CLASS ( Settings ) :: defaultMouseCursorEnabled },
        { C_ENG_CLASS ( Settings ) :: keyShowFramesPerSecond,                   C_ENG_CLASS ( Settings ) :: defaultShowFramesPerSecond },
        { C_ENG_CLASS ( Settings ) :: keyResolution,                            C_ENG_CLASS ( Settings ) :: defaultResolution },
        { C_ENG_CLASS ( Settings ) :: keyFieldOfView,                           C_ENG_CLASS ( Settings ) :: defaultFieldOfView },
        { C_ENG_CLASS ( Settings ) :: keyDrawDistance,                          C_ENG_CLASS ( Settings ) :: defaultDrawDistance }
};

auto C_ENG_CLASS ( Settings ) :: defaultForKey ( Key key ) noexcept -> Value {
    if ( defaults.containsKey ( String ( key ) ) ) {
        return defaults [ String ( key ) ];
    }

    return 0ULL;
}

C_ENG_CLASS ( Settings ) :: C_ENG_DESTRUCTOR ( Settings ) () noexcept {
    (void) this->save();
}

auto C_ENG_CLASS ( Settings ) :: save () noexcept -> C_ENG_TYPE ( Settings ) & {
    std :: fstream file ( defaultPath, std :: ios :: out | std :: ios :: trunc );

    for ( auto & pair : this->_settings ) {
        file << pair.first() << '=' << pair.second() << '\n';
    }

    return * this;
}