//
// Created by loghin on 20.12.2021.
//

#include "WindowResizeEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( WindowResizeEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( WindowResizeEvent ) ) " "
           "{ base = "    + this->__C_ENG_TYPE(WindowEvent)::toString() +
           ", size = "    + :: toString ( this->size() ) +
           ", oldSize = " + :: toString ( this->oldSize() ) +
           " }";
}

auto __C_ENG_TYPE ( WindowResizeEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( WindowResizeEvent ) const * > ( & object );

    return
        :: equals ( this->size(), pEvent->size() ) &&
        :: equals ( this->oldSize(), pEvent->oldSize() );
}