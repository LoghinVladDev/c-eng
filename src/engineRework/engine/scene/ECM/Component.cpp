//
// Created by loghin on 4/6/22.
//

#include "Component.hpp"
#include <Logger.hpp>
#include <scene/ECM/components/transform/Transform.hpp>

using namespace engine;
using namespace cds;

#define C_ENG_MAP_START CLASS ( Component, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

auto Self :: dumpTo ( json :: standard :: JsonObject & json ) noexcept -> Self & {

    (void) json.put ( Self :: typeKey, engine :: toString ( this->type() ) );
    return * this;
}

auto Self :: instantiate ( json :: standard :: JsonObject const & json ) noexcept (false) -> UniquePointer < Self > {

    try {
        auto componentTypeFlag = stringToComponentTypeFlag ( json.getString ( Self :: typeKey ) );

        try {
            auto component = Self :: instantiate ( componentTypeFlag );
            (void) component->loadFrom ( json );

            return component;

        } catch ( Exception const & exception ) {
            log :: err() << "Failed to instantiate component : " << exception.toString();
            throw;
        }

    } catch ( KeyException const & ) {
        log :: err() << "Component does not have a the type key '" << Self :: typeKey << "' inside configuration";
        throw;
    } catch ( TypeException const & typeException ) {
        log :: err () << "Component has a type key '" << Self :: typeKey << "', but it's format is invalid : " << typeException;
        throw;
    }
}

auto Self :: instantiate ( Type ( ComponentTypeFlag ) flag ) noexcept (false) -> UniquePointer < Self > {
    switch ( flag ) {
        case ComponentTypeFlagTransform:        return new Type ( Transform );
        default:
            break;
    }

    throw Exception ( "Invalid Flag Value for Component Instantiation : 0x" + Long ( flag ).toString(16) ); // NOLINT(readability-magic-numbers)
}
