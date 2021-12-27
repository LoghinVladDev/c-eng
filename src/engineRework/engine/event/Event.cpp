//
// Created by loghin on 20.12.2021.
//

#include "Event.hpp"

#include <CDS/Long>
#include <Window.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#undef __C_ENG_OBJECT_NAME
#define __C_ENG_OBJECT_NAME Event /* NOLINT(bugprone-reserved-identifier) */


auto __C_ENG_SELF :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_SELF ) " "
           "{ type = "_s            + :: toString ( this->type() ) +
           ", windowHandle = "      + :: toString ( this->window() ) +
           " }";
}

auto __C_ENG_SELF :: equals (
        Object const & object
) const noexcept -> bool {

    if ( this == & object ) {
        return true;
    }

    auto pEvent = dynamic_cast < __C_ENG_SELF const * > ( & object );
    if ( pEvent == nullptr ) {
        return false;
    }

    return this->type() == pEvent->type() && this->window() == pEvent->window();
}