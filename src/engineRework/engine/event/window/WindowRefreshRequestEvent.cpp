//
// Created by loghin on 21.12.2021.
//

#include "WindowRefreshRequestEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( WindowRefreshRequestEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( WindowRefreshRequestEvent ) ) " "
           "{ base = "   + this->__C_ENG_TYPE(WindowEvent)::toString() +
           " }";
}