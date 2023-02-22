//
// Created by loghin on 21.12.2021.
//

#include "WindowGainFocusEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( WindowGainFocusEvent, ENGINE_PARENT ( WindowEvent ) )
#include <ObjectMapping.hpp>

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "   + this-> Parent :: toString() +
           " }";
}
