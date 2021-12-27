//
// Created by loghin on 22.12.2021.
//

#include "Joystick.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

__C_ENG_TYPE ( Joystick ) :: __C_ENG_DESTRUCTOR ( Joystick ) () noexcept {
    delete[] this->_axes;
    delete[] this->_buttons;
    delete[] this->_hats;
}

#include <Core.hpp>

auto __C_ENG_TYPE ( Joystick ) :: toString () const noexcept -> String {
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
            asString += :: toString ( static_cast < __C_ENG_TYPE ( ControllerHatState ) > ( hats[i] ) );
        }

        return asString;
    };

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Joystick ) ) " "
           "{ base = "      + this->__C_ENG_TYPE(Controller)::toString() +
           ", axes = "      + axesToString ( this->axes(), this->axisCount() ) +
           ", buttons = "   + buttonsToString ( this->buttons(), this->buttonCount() ) +
           ", hats = "      + hatsToString ( this->hats(), this->hatCount() ) +
           " }";
}