//
// Created by loghin on 20.12.2021.
//

#include "MouseScrollEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( MouseScrollEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MouseScrollEvent ) ) " "
           "{ base = "      + this->__C_ENG_TYPE(MouseEvent)::toString() +
           ", xOffset = "   + this->xOffset() +
           ", yOffset = "   + this->yOffset() +
           " }";
}

auto __C_ENG_TYPE ( MouseScrollEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(MouseEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( MouseScrollEvent ) const * > ( & object );

    return
        this->xOffset() == pEvent->xOffset() &&
        this->yOffset() == pEvent->yOffset();
}