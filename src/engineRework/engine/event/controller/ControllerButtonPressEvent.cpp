//
// Created by loghin on 22.12.2021.
//

#include "ControllerButtonPressEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( ControllerButtonPressEvent, ENGINE_PARENT ( ControllerEvent ) )
#include <ObjectMapping.hpp>

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "    + this-> Parent :: toString() +
           ", button = "  + this->button() +
           " }";
}

auto Self :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this-> Parent :: equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < Self const * > ( & object );

    return this->button() == pEvent->button(); // NOLINT(clion-misra-cpp2008-5-0-4)
}