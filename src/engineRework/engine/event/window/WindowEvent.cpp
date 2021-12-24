//
// Created by loghin on 21.12.2021.
//

#include "WindowEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( WindowEvent ) :: toString () const noexcept -> String {
    return "WindowEvent "
           "{ Event = " + this->C_ENG_CLASS(Event)::toString() +
           " }";
}