//
// Created by loghin on 22.12.2021.
//

#include "ControllerDisconnectEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( ControllerDisconnectEvent ) :: toString () const noexcept -> String {
    return "ControllerDisconnectEvent "
           "{ ControllerEvent = "   + this->C_ENG_CLASS(ControllerEvent)::toString() +
           " }";
}

