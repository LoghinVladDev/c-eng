//
// Created by loghin on 19.12.2021.
//

#include "Settings.hpp"

#include <Logger.hpp>

#include <CDS/Path>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( Settings, PARENT ( Object ) )
#include <ObjectMapping.hpp>

auto Self :: instance () noexcept -> Self & {
    static Self settings;

    if ( ! settings.initialized() ) {
        (void) settings.load();
    }

    return settings;
}

auto Self :: load () noexcept -> Self & {

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

auto Self :: get ( Key key ) noexcept -> Value {
    if ( ! this->_settings.containsKey ( key ) ) {
        this->_settings [ String ( key ) ] = Self :: defaultForKey ( key );
    }

    return this->_settings [ String ( key ) ];
}

auto Self :: set ( Key key, Value value ) noexcept -> Self & {
    this->_settings [ String (key) ] = value;

    return * this;
}

static HashMap < String, Self :: Value > defaults = {
        { __C_ENG_TYPE ( Settings ) :: keyUseValidationLayers,                   __C_ENG_TYPE ( Settings ) :: defaultUseValidationLayers },
        { __C_ENG_TYPE ( Settings ) :: keyLogToConsole,                          __C_ENG_TYPE ( Settings ) :: defaultLogToConsole },
        { __C_ENG_TYPE ( Settings ) :: keyPeriodicCacheReconstructionInterval,   __C_ENG_TYPE ( Settings ) :: defaultPeriodicCacheReconstructionInterval },
        { __C_ENG_TYPE ( Settings ) :: keyMouseCursorEnabled,                    __C_ENG_TYPE ( Settings ) :: defaultMouseCursorEnabled },
        { __C_ENG_TYPE ( Settings ) :: keyShowFramesPerSecond,                   __C_ENG_TYPE ( Settings ) :: defaultShowFramesPerSecond },
        { __C_ENG_TYPE ( Settings ) :: keyResolution,                            __C_ENG_TYPE ( Settings ) :: defaultResolution },
        { __C_ENG_TYPE ( Settings ) :: keyFieldOfView,                           __C_ENG_TYPE ( Settings ) :: defaultFieldOfView },
        { __C_ENG_TYPE ( Settings ) :: keyDrawDistance,                          __C_ENG_TYPE ( Settings ) :: defaultDrawDistance }
};

auto Self :: defaultForKey ( Key key ) noexcept -> Value {
    if ( defaults.containsKey ( String ( key ) ) ) {
        return defaults [ String ( key ) ];
    }

    return 0ULL;
}

Self :: Destructor () noexcept {
    (void) this->save();
}

auto Self :: save () noexcept -> Self & {
    std :: fstream file ( defaultPath, std :: ios :: out | std :: ios :: trunc );

    for ( auto & pair : this->_settings ) {
        file << pair.first() << '=' << pair.second() << '\n';
    }

    return * this;
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ initialized = "_s + :: toString ( this->initialized() ) +
           ", settings = "      + this->_settings.toString();
}