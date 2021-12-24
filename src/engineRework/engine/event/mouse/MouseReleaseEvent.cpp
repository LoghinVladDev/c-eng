//
// Created by loghin on 20.12.2021.
//

#include "MouseReleaseEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( MouseReleaseEvent ) :: toString () const noexcept -> String {
    return "MouseReleaseEvent "
           "{ MouseEvent = "    + this->C_ENG_CLASS(MouseEvent)::toString() +
           ", button = "        + :: toString ( this->button() ) +
           ", modifiers = "     + :: keyModifiersToString ( this->modifiers() ) +
           " }";
}

auto C_ENG_CLASS ( MouseReleaseEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(MouseEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( MouseReleaseEvent ) const * > ( & object );

    return
            this->button() == pEvent->button() &&
            this->modifiers() == pEvent->modifiers();
}
