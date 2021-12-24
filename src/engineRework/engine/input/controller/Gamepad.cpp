//
// Created by loghin on 22.12.2021.
//

#include "Gamepad.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Core.hpp>

auto C_ENG_CLASS ( Gamepad ) :: toString () const noexcept -> String {
    static auto axesToString = []( float const * axes ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  C_ENG_CLASS ( Gamepad ) :: axesCount; ++ i ) {
            asString += axes[i] + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    static auto buttonsToString = []( bool const * buttons ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  C_ENG_CLASS ( Gamepad ) :: buttonCount; ++ i ) {
            asString += :: toString ( buttons[i] ) + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    return "Gamepad "
           "{ Controller = "    + this->C_ENG_CLASS(Controller)::toString() +
           ", gamepadName = "   + this->gamepadName() +
           ", axes = "          + axesToString ( this->_axes ) +  // NOLINT(clion-misra-cpp2008-5-2-12)
           ", buttons = "       + buttonsToString ( this->_buttons ) +  // NOLINT(clion-misra-cpp2008-5-2-12)
           " }";
}
