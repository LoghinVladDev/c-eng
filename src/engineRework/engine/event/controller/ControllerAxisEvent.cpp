//
// Created by loghin on 22.12.2021.
//

#include "ControllerAxisEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

auto __C_ENG_TYPE ( ControllerAxisEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ControllerAxisEvent ) ) " "
           "{ base = "      + this->__C_ENG_TYPE(ControllerEvent)::toString() +
           ", axis = "      + this->axis() +
           ", value = "     + this->value() +
           ", oldValue = "  + this->oldValue() +
           " }";
}

auto __C_ENG_TYPE ( ControllerAxisEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(ControllerEvent)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( ControllerAxisEvent ) const * > ( & object );

    return this->axis() == pEvent->axis(); // NOLINT(clion-misra-cpp2008-5-0-4)
}