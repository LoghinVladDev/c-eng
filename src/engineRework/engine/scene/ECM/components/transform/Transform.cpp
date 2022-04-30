//
// Created by loghin on 4/30/22.
//

#include "Transform.hpp"
#include <Logger.hpp>

using namespace cds;
using namespace engine;

#define C_ENG_MAP_START CLASS ( Transform, ENGINE_PARENT ( Component ) )
#include <ObjectMapping.hpp>

auto Self :: loadFrom ( cds :: json :: standard :: JsonObject const & object ) noexcept -> Self & {

    try {
        auto const & locationObject = object.getJson ( Self :: locationKey );

        this->_location.x = locationObject.getFloat ( Self :: locationXKey );
        this->_location.y = locationObject.getFloat ( Self :: locationYKey );
        this->_location.z = locationObject.getFloat ( Self :: locationZKey );
    } catch ( KeyException const & ) {
        log :: warn() << "Key '" << Self :: locationKey << "' not present in component";
    } catch ( TypeException const & ) {
        log :: warn() << "Key '" << Self :: locationKey << "' present, but format is not ok";
    }

    try {
        auto const & rotationObject = object.getJson ( Self :: rotationKey );

        (void) this->_rotation.set (
                rotationObject.getFloat ( Self :: rotationYawKey ),
                rotationObject.getFloat ( Self :: rotationPitchKey ),
                rotationObject.getFloat ( Self :: rotationRollKey )
        );
    } catch ( KeyException const & ) {
        log :: warn() << "Key '" << Self :: rotationKey << "' not present in component";
    } catch ( TypeException const & ) {
        log :: warn() << "Key '" << Self :: rotationKey << "' present, but format is not ok";
    }

    try {
        auto const & scaleObject = object.getJson ( Self :: scaleKey );

        this->_scale.x = scaleObject.getFloat ( Self :: scaleXKey );
        this->_scale.y = scaleObject.getFloat ( Self :: scaleYKey );
        this->_scale.z = scaleObject.getFloat ( Self :: scaleZKey );
    } catch ( KeyException const & ) {
        log :: warn() << "Key '" << Self :: scaleKey << "' not present in component";
    } catch ( TypeException const & ) {
        log :: warn() << "Key '" << Self :: scaleKey << "' present, but format is not ok";
    }

    return * this;
}

auto Self :: dumpTo ( json :: standard :: JsonObject & object ) noexcept -> Self & {

    object.put (
                    Self :: locationKey,
                    json :: standard :: JsonObject ()
                            .put ( Self :: locationXKey, this->_location.x )
                            .put ( Self :: locationYKey, this->_location.y )
                            .put ( Self :: locationZKey, this->_location.z )
            ).put (
                    Self :: rotationKey,
                    json :: standard :: JsonObject ()
                            .put ( Self :: rotationYawKey, this->_rotation.yaw() )
                            .put ( Self :: rotationPitchKey, this->_rotation.pitch() )
                            .put ( Self :: rotationRollKey, this->_rotation.roll() )
            ).put (
                    Self :: scaleKey,
                    json :: standard :: JsonObject ()
                            .put ( Self :: scaleXKey,   this->_scale.x )
                            .put ( Self :: scaleYKey,   this->_scale.y )
                            .put ( Self :: scaleZKey,   this->_scale.z )
            );

    return * this;
}

auto Self :: clear () noexcept -> Self & {

    this->_location = glm :: vec3 ( 0.0F );
    this->_scale    = glm :: vec3 ( 0.0F );
    this->_rotation = Type ( Rotor ) ();

    return * this;
}

auto Self :: copy () const noexcept -> Self * {
    return new Self ( * this );
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Type ( Transform ) ) +
            "{ location = "_s +
                    "( x = " + this->_location.x +
                    ", y = " + this->_location.y +
                    ", z = " + this->_location.z +
            " ), rotation = " +
                    "( yaw = "      + this->_rotation.yaw() +
                    ", pitch = "    + this->_rotation.pitch() +
                    ", roll = "     + this->_rotation.roll() +
            " ), scale = " +
                    "( x = " + this->_scale.x +
                    ", y = " + this->_scale.y +
                    ", z = " + this->_scale.z +
            " ) }";
}
