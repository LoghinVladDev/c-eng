//
// Created by loghin on 20.12.2021.
//

#include "KeyReleaseEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( KeyReleaseEvent, ENGINE_PARENT ( KeyEvent ) )
#include <ObjectMapping.hpp>

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "  + this-> Parent :: toString() +
           " }";
}
