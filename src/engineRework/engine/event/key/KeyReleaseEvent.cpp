//
// Created by loghin on 20.12.2021.
//

#include "KeyReleaseEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( KeyReleaseEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( KeyReleaseEvent ) ) " "
           "{ base = "  + this->__C_ENG_TYPE(KeyEvent)::toString() +
           " }";
}
