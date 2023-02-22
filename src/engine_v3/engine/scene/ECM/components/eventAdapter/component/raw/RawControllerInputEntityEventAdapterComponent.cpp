//
// Created by loghin on 5/1/22.
//

#include "RawControllerInputEntityEventAdapterComponent.hpp"
#include <scene/ECM/components/eventAdapter/EntityEventAdapter.hpp>
#include <scene/ECM/Entity.hpp>

using namespace engine;
using namespace cds;
using namespace cds :: json :: standard;

#define C_ENG_MAP_START CLASS ( RawControllerInputEntityEventAdapterComponent, ENGINE_PARENT ( EntityEventAdapterControllerComponent ) )
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

auto Self :: controllerAxisEvent ( Type ( ControllerAxisEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->controllerAxisEvent ( pEvent );
}

auto Self :: controllerButtonPressEvent ( Type ( ControllerButtonPressEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->controllerButtonPressEvent ( pEvent );
}

auto Self :: controllerButtonReleaseEvent ( Type ( ControllerButtonReleaseEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->controllerButtonReleaseEvent ( pEvent );
}

auto Self :: controllerHatEvent ( Type ( ControllerHatEvent ) * pEvent ) noexcept -> void {
    this->adapter()->entity()->controllerHatEvent ( pEvent );
}
