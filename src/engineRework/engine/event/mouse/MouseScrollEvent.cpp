//
// Created by loghin on 20.12.2021.
//

#include "MouseScrollEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( MouseScrollEvent ) :: toString () const noexcept -> String {
    return "MouseScrollEvent "
           "{ MouseEvent = "    + this->C_ENG_CLASS(MouseEvent)::toString() +
           ", xOffset = "       + this->xOffset() +
           ", yOffset = "       + this->yOffset() +
           " }";
}

auto C_ENG_CLASS ( MouseScrollEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(MouseEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( MouseScrollEvent ) const * > ( & object );

    return
        this->xOffset() == pEvent->xOffset() &&
        this->yOffset() == pEvent->yOffset();
}