//
// Created by loghin on 5/2/22.
//

#include "EntityEventAdapterMouseComponent.hpp"

#include <scene/ECM/components/eventAdapter/component/raw/RawMouseInputEntityEventAdapterComponent.hpp>

#include <Logger.hpp>

using namespace cds;
using namespace engine;
using namespace cds :: json :: standard;

#define C_ENG_MAP_START CLASS ( EntityEventAdapterMouseComponent, ENGINE_PARENT ( EngineObject ) )
#include <ObjectMapping.hpp>

auto Self :: dumpTo ( JsonObject & json ) noexcept -> Self & {

    json.put ( Self :: typeKey, engine :: toString ( this->type() ) );
    return * this;
}

auto Self :: instantiate ( Type ( EntityEventAdapterMouseComponentType ) type ) noexcept (false) -> UniquePointer < Self > {

    switch ( type ) {

        case EntityEventAdapterMouseComponentTypeRawInput:   return new Type ( RawMouseInputEntityEventAdapterComponent ) ();
        default:
            break;
    }

    throw Exception ( "Invalid Flag Value for Component Instantiation : "_s + engine :: toString ( type ) );
}

auto Self :: instantiate ( JsonObject const & json ) noexcept (false) -> UniquePointer < Self > {

    try {
        auto pComponent = Self :: instantiate ( stringToEntityEventAdapterMouseComponentType ( json.getString ( Self :: typeKey ) ) );
        pComponent->loadFrom ( json );

        return pComponent;

    } catch ( KeyException const & ) {
        log :: err()
                << "EventAdapterComponent does not have a '"
                << Self :: typeKey
                << "' key";

        throw;
    } catch ( TypeException const & typeException ) {
        log :: err()
                << "EventAdapterComponent has a '"
                << Self :: typeKey
                << "' key, but format is not ok : "
                << typeException.toString();
        throw;
    }
}
