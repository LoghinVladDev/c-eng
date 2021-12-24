//
// Created by loghin on 22.12.2021.
//

#include "ControllerEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Controller.hpp>

auto C_ENG_CLASS ( ControllerEvent ) :: hash () const noexcept -> Index {
    return this->controller()->handle();
}

auto C_ENG_CLASS ( ControllerEvent ) :: toString () const noexcept -> String {
    return "ControllerEvent "
           "{ event = "             + this->C_ENG_CLASS(Event)::toString() +
           ", controllerHandle = "  + Int ( this->controller()->handle() ).toString() +
           " }";
}

auto C_ENG_CLASS ( ControllerEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( ControllerEvent ) const * > ( & object );

    return this->controller() == pEvent->controller();
}