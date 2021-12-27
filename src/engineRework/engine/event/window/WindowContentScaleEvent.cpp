//
// Created by loghin on 21.12.2021.
//

#include "WindowContentScaleEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( WindowContentScaleEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( WindowContentScaleEvent ) ) " "
           "{ base = "    + this->__C_ENG_TYPE(WindowEvent)::toString() +
           ", scale = "   + :: toString ( this->scale() ) +
           " }";
}

auto __C_ENG_TYPE ( WindowContentScaleEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( WindowContentScaleEvent ) const * > ( & object );

    return :: equals ( this->scale(), pEvent->scale() );
}