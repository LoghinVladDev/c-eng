//
// Created by loghin on 22.12.2021.
//

#include "Joystick.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

C_ENG_CLASS ( Joystick ) :: C_ENG_DESTRUCTOR ( Joystick ) () noexcept {
    delete[] this->_axes;
    delete[] this->_buttons;
    delete[] this->_hats;
}

#include <Core.hpp>

auto C_ENG_CLASS ( Joystick ) :: toString () const noexcept -> String {
    static auto axesToString = []( float const * axes, uint32 axisCount ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  axisCount; ++ i ) {
            asString += axes[i] + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    static auto buttonsToString = []( bool const * buttons, uint32 buttonCount ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  buttonCount; ++ i ) {
            asString += :: toString ( buttons[i] ) + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    static auto hatsToString = []( cds :: uint8 * hats, uint32 hatCount ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i < hatCount; ++ i ) {
            asString += :: toString ( static_cast < ControllerHatState > ( hats[i] ) );
        }

        return asString;
    };

    return "Joystick "
           "{ Controller = "    + this->C_ENG_CLASS(Controller)::toString() +
           ", axes = "          + axesToString ( this->axes(), this->axisCount() ) +
           ", buttons = "       + buttonsToString ( this->buttons(), this->buttonCount() ) +
           ", hats = "          + hatsToString ( this->hats(), this->hatCount() ) +
           " }";
}