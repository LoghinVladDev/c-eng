//
// Created by loghin on 20.12.2021.
//

#include "MouseMoveEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( MouseMoveEvent ) :: toString () const noexcept -> String {
    return "MouseMoveEvent "
           "{ MouseEvent = "    + this->C_ENG_CLASS(MouseEvent)::toString() +
           ", oldPosition = "   + :: toString ( this->oldPosition() ) +
           " }";
}

auto C_ENG_CLASS ( MouseMoveEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(MouseEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( MouseMoveEvent ) const * > ( & object );

    return :: equals ( this->oldPosition(), pEvent->oldPosition() );
}