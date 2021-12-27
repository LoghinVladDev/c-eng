//
// Created by loghin on 22.12.2021.
//

#include "ControllerButtonPressEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME ControllerButtonPressEvent /* NOLINT(bugprone-reserved-identifier) */


auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
           "{ base = "    + this->__C_ENG_TYPE(ControllerEvent)::toString() +
           ", button = "  + this->button() +
           " }";
}

auto __C_ENG_SELF :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(ControllerEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_SELF const * > ( & object );

    return this->button() == pEvent->button(); // NOLINT(clion-misra-cpp2008-5-0-4)
}