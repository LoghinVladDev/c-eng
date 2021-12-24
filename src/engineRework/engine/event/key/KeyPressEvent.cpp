//
// Created by loghin on 20.12.2021.
//

#include "KeyPressEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( KeyPressEvent ) :: toString () const noexcept -> String {
    return "KeyPressEvent "
           "{ KeyEvent = "  + this->C_ENG_CLASS(KeyEvent)::toString() +
           " }";
}