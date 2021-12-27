//
// Created by loghin on 21.12.2021.
//

#include "WindowRestoreEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( WindowRestoreEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( WindowRestoreEvent ) ) " "
           "{ base = "   + this->__C_ENG_TYPE(WindowEvent)::toString() +
           " }";
}
