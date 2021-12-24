//
// Created by loghin on 21.12.2021.
//

#include "WindowMoveEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( WindowMoveEvent ) :: toString () const noexcept -> String {
    return "WindowMoveEvent "
           "{ WindowEvent = "   + this->C_ENG_CLASS(WindowEvent)::toString() +
           ", position = "      + :: toString ( this->position() ) +
           ", oldPosition = "   + :: toString ( this->oldPosition() ) +
           " }";
}

auto C_ENG_CLASS ( WindowMoveEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( WindowMoveEvent ) const * > ( & object );

    return
        :: equals ( this->position(), pEvent->position() ) &&
        :: equals ( this->oldPosition(), pEvent->oldPosition() );
}