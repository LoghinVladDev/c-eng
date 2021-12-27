//
// Created by loghin on 20.12.2021.
//

#include "MouseReleaseEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( MouseReleaseEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( MouseReleaseEvent ) ) " "
           "{ base = "      + this->__C_ENG_TYPE(MouseEvent)::toString() +
           ", button = "    + :: toString ( this->button() ) +
           ", modifiers = " + :: keyModifiersToString ( this->modifiers() ) +
           " }";
}

auto __C_ENG_TYPE ( MouseReleaseEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(MouseEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( MouseReleaseEvent ) const * > ( & object );

    return
            this->button() == pEvent->button() &&
            this->modifiers() == pEvent->modifiers();
}
