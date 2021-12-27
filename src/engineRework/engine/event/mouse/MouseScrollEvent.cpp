//
// Created by loghin on 20.12.2021.
//

#include "MouseScrollEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME MouseScrollEvent /* NOLINT(bugprone-reserved-identifier) */


auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
           "{ base = "      + this->__C_ENG_TYPE(MouseEvent)::toString() +
           ", xOffset = "   + this->xOffset() +
           ", yOffset = "   + this->yOffset() +
           " }";
}

auto __C_ENG_SELF :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(MouseEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_SELF const * > ( & object );

    return
        this->xOffset() == pEvent->xOffset() &&
        this->yOffset() == pEvent->yOffset();
}