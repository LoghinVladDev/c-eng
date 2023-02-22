//
// Created by loghin on 5/1/22.
//

#include "RawKeyInputEntityEventAdapterComponent.hpp"
#include <scene/ECM/components/eventAdapter/EntityEventAdapter.hpp>
#include <scene/ECM/Entity.hpp>

using namespace engine;
using namespace cds;
using namespace cds :: json :: standard;

#define C_ENG_MAP_START CLASS ( RawKeyInputEntityEventAdapterComponent, ENGINE_PARENT ( EntityEventAdapterKeyComponent ) )
#include <ObjectMapping.hpp>

auto Self :: loadFrom ( JsonObject const & json ) noexcept -> Self & {
    return * this;
}

auto Self :: dumpTo ( JsonObject & json ) noexcept -> Self & {
    (void) this->Parent :: dumpTo ( json );

    return * this;
}

auto Self :: clear () noexcept -> Self & {
    return * this;
}

auto Self :: copy () const noexcept -> Self * {
    return new Self ( * this );
}

Self :: Destructor () noexcept {
    (void) this->Self::clear();
}

auto Self :: keyPressEvent ( Type ( KeyPressEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->keyPressEvent ( pEvent );
}

auto Self :: keyReleaseEvent ( Type ( KeyReleaseEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->keyReleaseEvent ( pEvent );
}
