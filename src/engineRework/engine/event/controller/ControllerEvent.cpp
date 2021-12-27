//
// Created by loghin on 22.12.2021.
//

#include "ControllerEvent.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Controller.hpp>

auto __C_ENG_TYPE ( ControllerEvent ) :: hash () const noexcept -> Index {
    return this->controller()->handle();
}

auto __C_ENG_TYPE ( ControllerEvent ) :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( ControllerEvent ) ) " "
           "{ base = "              + this->__C_ENG_TYPE(Event)::toString() +
           ", controllerHandle = "  + Int ( this->controller()->handle() ).toString() +
           " }";
}

auto __C_ENG_TYPE ( ControllerEvent ) :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this->__C_ENG_TYPE(Event)::equals(object) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < __C_ENG_TYPE ( ControllerEvent ) const * > ( & object );

    return this->controller() == pEvent->controller();
}