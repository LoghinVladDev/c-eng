//
// Created by loghin on 20.12.2021.
//

#include "Event.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <CDS/Long>
#include <Window.hpp>

auto C_ENG_CLASS ( Event ) :: toString () const noexcept -> String {
    return "Event "
           "{ windowHandle = "      + :: toString ( this->window() ) +
           ", type = "              + :: toString ( this->type() ) +
           "}";
}

auto C_ENG_CLASS ( Event ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( this == & object ) {
        return true;
    }

    auto pEvent = dynamic_cast < C_ENG_TYPE ( Event ) const * > ( & object );
    if ( pEvent == nullptr ) {
        return false;
    }

    return this->type() == pEvent->type() && this->window() == pEvent->window();
}