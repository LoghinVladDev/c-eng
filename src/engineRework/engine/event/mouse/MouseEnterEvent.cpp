//
// Created by loghin on 20.12.2021.
//

#include "MouseEnterEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( MouseEnterEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MouseEnterEvent ) ) " "
           "{ base = "    + this->__C_ENG_TYPE(MouseEvent)::toString() +
           " }";
}
