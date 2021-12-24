//
// Created by loghin on 22.12.2021.
//

#include "ControllerHatEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( ControllerHatEvent ) :: toString () const noexcept -> String {
    return "ControllerHatEvent "
           "{ ControllerEvent = "   + this->C_ENG_CLASS(ControllerEvent)::toString() +
           ", hat = "               + this->hat() +
           ", state = "             + :: toString ( this->state() ) +
           " }";
}

auto C_ENG_CLASS ( ControllerHatEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(ControllerEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( ControllerHatEvent ) const * > ( & object );

    return this->hat() == pEvent->hat(); // NOLINT(clion-misra-cpp2008-5-0-4)
}