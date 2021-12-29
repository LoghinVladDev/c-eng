//
// Created by loghin on 20.12.2021.
//

#include "Event.hpp"

#include <CDS/Long>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( Event, NO_PARENT )
#include <ObjectMapping.hpp>

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ type = "_s            + :: toString ( this->type() ) +
           ", windowHandle = "      + :: toString ( this->window() ) +
           " }";
}

auto Self :: equals (
        Object const & object
) const noexcept -> bool {

    if ( this == & object ) {
        return true;
    }

    auto pEvent = dynamic_cast < Self const * > ( & object );
    if ( pEvent == nullptr ) {
        return false;
    }

    return this->type() == pEvent->type() && this->window() == pEvent->window();
}