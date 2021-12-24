//
// Created by loghin on 22.12.2021.
//

#include "ControllerButtonPressEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( ControllerButtonPressEvent ) :: toString () const noexcept -> String {
    return "ControllerButtonPressEvent "
           "{ ControllerEvent = "   + this->C_ENG_CLASS(ControllerEvent)::toString() +
           ", button = "            + this->button() +
           " }";
}

auto C_ENG_CLASS ( ControllerButtonPressEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(ControllerEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( ControllerButtonPressEvent ) const * > ( & object );

    return this->button() == pEvent->button(); // NOLINT(clion-misra-cpp2008-5-0-4)
}