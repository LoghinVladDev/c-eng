//
// Created by loghin on 22.12.2021.
//

#include "Gamepad.hpp"

#include <Core.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( Gamepad, ENGINE_PARENT ( Controller ) )
#include <ObjectMapping.hpp>

auto Self :: toString () const noexcept -> String {
    static auto axesToString = []( float const * axes ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  Self :: axesCount; ++ i ) {
            asString += axes[i] + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    static auto buttonsToString = []( bool const * buttons ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  Self :: buttonCount; ++ i ) {
            asString += :: toString ( buttons[i] ) + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "          + this-> Parent :: toString() +
           ", gamepadName = "   + this->gamepadName() +
           ", axes = "          + axesToString ( this->_axes ) +  // NOLINT(clion-misra-cpp2008-5-2-12)
           ", buttons = "       + buttonsToString ( this->_buttons ) +  // NOLINT(clion-misra-cpp2008-5-2-12)
           " }";
}
