//
// Created by loghin on 21.12.2021.
//

#include "WindowMinimizeEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( WindowMinimizeEvent ) :: toString () const noexcept -> String {
    return "WindowMinimizeEvent "
           "{ WindowEvent = "   + this->C_ENG_CLASS(WindowEvent)::toString() +
           " }";
}
