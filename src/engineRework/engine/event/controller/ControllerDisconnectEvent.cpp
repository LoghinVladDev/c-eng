//
// Created by loghin on 22.12.2021.
//

#include "ControllerDisconnectEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME ControllerDisconnectEvent /* NOLINT(bugprone-reserved-identifier) */


auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
           "{ base = "   + this->__C_ENG_TYPE(ControllerEvent)::toString() +
           " }";
}

