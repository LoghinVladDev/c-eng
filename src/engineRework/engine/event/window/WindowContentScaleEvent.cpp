//
// Created by loghin on 21.12.2021.
//

#include "WindowContentScaleEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( WindowContentScaleEvent ) :: toString () const noexcept -> String {
    return "WindowContentScaleEvent "
           "{ WindowEvent = "   + this->C_ENG_CLASS(WindowEvent)::toString() +
           ", scale = "         + :: toString ( this->scale() ) +
           " }";
}

auto C_ENG_CLASS ( WindowContentScaleEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( WindowContentScaleEvent ) const * > ( & object );

    return :: equals ( this->scale(), pEvent->scale() );
}