//
// Created by loghin on 20.12.2021.
//

#include "MouseLeaveEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( MouseLeaveEvent ) :: toString () const noexcept -> String {
    return "MouseLeaveEvent "
           "{ MouseEvent = "    + this->C_ENG_CLASS(MouseEvent)::toString() +
           " }";
}
