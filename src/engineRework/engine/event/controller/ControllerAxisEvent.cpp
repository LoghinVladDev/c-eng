//
// Created by loghin on 22.12.2021.
//

#include "ControllerAxisEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( ControllerAxisEvent ) :: toString () const noexcept -> String {
    return "ControllerAxisEvent "
           "{ ControllerEvent = "   + this->C_ENG_CLASS(ControllerEvent)::toString() +
           ", axis = "              + this->axis() +
           ", value = "             + this->value() +
           ", oldValue = "          + this->oldValue() +
           " }";
}

auto C_ENG_CLASS ( ControllerAxisEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(ControllerEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( ControllerAxisEvent ) const * > ( & object );

    return this->axis() == pEvent->axis(); // NOLINT(clion-misra-cpp2008-5-0-4)
}