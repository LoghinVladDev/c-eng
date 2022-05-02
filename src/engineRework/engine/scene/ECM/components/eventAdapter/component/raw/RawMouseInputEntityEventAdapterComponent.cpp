//
// Created by loghin on 5/1/22.
//

#include "RawMouseInputEntityEventAdapterComponent.hpp"
#include <scene/ECM/components/eventAdapter/EntityEventAdapter.hpp>
#include <scene/ECM/Entity.hpp>

using namespace engine;
using namespace cds;
using namespace cds :: json :: standard;

#define C_ENG_MAP_START CLASS ( RawMouseInputEntityEventAdapterComponent, ENGINE_PARENT ( EntityEventAdapterMouseComponent ) )
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

auto Self :: mouseMoveEvent ( Type ( MouseMoveEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->mouseMoveEvent ( pEvent );
}

auto Self :: mousePressEvent ( Type ( MousePressEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->mousePressEvent ( pEvent );
}

auto Self :: mouseReleaseEvent ( Type ( MouseReleaseEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->mouseReleaseEvent ( pEvent );
}

auto Self :: mouseScrollEvent ( Type ( MouseScrollEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->mouseScrollEvent ( pEvent );
}
