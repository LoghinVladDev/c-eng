//
// Created by loghin on 20.12.2021.
//

#include "MousePressEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( MousePressEvent, ENGINE_PARENT ( MouseEvent ) )
#include <ObjectMapping.hpp>

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "      + this-> Parent :: toString() +
           ", button = "    + :: toString ( this->button() ) +
           ", modifiers = " + :: keyModifiersToString ( this->modifiers() ) +
           " }";
}

auto Self :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this-> Parent :: equals ( object ) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < Self const * > ( & object );

    return
        this->button() == pEvent->button() &&
        this->modifiers() == pEvent->modifiers();
}