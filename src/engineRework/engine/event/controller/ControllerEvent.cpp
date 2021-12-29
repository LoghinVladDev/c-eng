//
// Created by loghin on 22.12.2021.
//

#include "ControllerEvent.hpp"

#include <Controller.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( ControllerEvent, ENGINE_PARENT ( Event ) )
#include <ObjectMapping.hpp>

auto Self :: hash () const noexcept -> Index {
    return this->controller()->handle();
}

auto Self :: toString () const noexcept -> String {
    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "              + this-> Parent :: toString() +
           ", controllerHandle = "  + Int ( this->controller()->handle() ).toString() +
           " }";
}

auto Self :: equals (
        Object const & object
) const noexcept -> bool {

    if ( ! this-> Parent :: equals ( object ) ) {
        return false;
    }

    auto pEvent = reinterpret_cast < Self const * > ( & object );

    return this->controller() == pEvent->controller();
}