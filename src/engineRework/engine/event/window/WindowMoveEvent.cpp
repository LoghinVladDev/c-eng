//
// Created by loghin on 21.12.2021.
//

#include "WindowMoveEvent.hpp"


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( WindowMoveEvent, ENGINE_PARENT ( WindowEvent ) )
#include <ObjectMapping.hpp>

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "          + this-> Parent :: toString() +
           ", position = "      + :: toString ( this->position() ) +
           ", oldPosition = "   + :: toString ( this->oldPosition() ) +
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
        :: equals ( this->position(), pEvent->position() ) &&
        :: equals ( this->oldPosition(), pEvent->oldPosition() );
}