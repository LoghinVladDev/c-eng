//
// Created by loghin on 21.12.2021.
//

#include "WindowMoveEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( WindowMoveEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( WindowMoveEvent ) ) " "
           "{ base = "          + this->__C_ENG_TYPE(WindowEvent)::toString() +
           ", position = "      + :: toString ( this->position() ) +
           ", oldPosition = "   + :: toString ( this->oldPosition() ) +
           " }";
}

auto __C_ENG_TYPE ( WindowMoveEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( WindowMoveEvent ) const * > ( & object );

    return
        :: equals ( this->position(), pEvent->position() ) &&
        :: equals ( this->oldPosition(), pEvent->oldPosition() );
}