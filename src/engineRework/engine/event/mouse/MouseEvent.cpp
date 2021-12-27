//
// Created by loghin on 20.12.2021.
//

#include "MouseEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( MouseEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MouseEvent ) ) " "
           "{ base = "      + this->__C_ENG_TYPE(Event)::toString() +
           ", position = "  + :: toString ( this->position() ) +
           " }";
}

auto __C_ENG_TYPE ( MouseEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( MouseEvent ) const * > ( & object );

    return :: equals ( this->position(), pEvent->position() );
}