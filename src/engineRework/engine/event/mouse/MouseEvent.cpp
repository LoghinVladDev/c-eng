//
// Created by loghin on 20.12.2021.
//

#include "MouseEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( MouseEvent ) :: toString () const noexcept -> String {
    return "MouseEvent "
           "{ Event = "     + this->C_ENG_CLASS(Event)::toString() +
           "{ position = "  + :: toString ( this->position() ) +
           " }";
}

auto C_ENG_CLASS ( MouseEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( MouseEvent ) const * > ( & object );

    return :: equals ( this->position(), pEvent->position() );
}