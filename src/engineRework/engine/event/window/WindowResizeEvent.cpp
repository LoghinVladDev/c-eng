//
// Created by loghin on 20.12.2021.
//

#include "WindowResizeEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto C_ENG_CLASS ( WindowResizeEvent ) :: toString () const noexcept -> String {
    return "WindowResizeEvent "
           "{ WindowEvent = "   + this->C_ENG_CLASS(WindowEvent)::toString() +
           ", size = "          + :: toString ( this->size() ) +
           ", oldSize = "       + :: toString ( this->oldSize() ) +
           " }";
}

auto C_ENG_CLASS ( WindowResizeEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->C_ENG_CLASS(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < C_ENG_TYPE ( WindowResizeEvent ) const * > ( & object );

    return
        :: equals ( this->size(), pEvent->size() ) &&
        :: equals ( this->oldSize(), pEvent->oldSize() );
}