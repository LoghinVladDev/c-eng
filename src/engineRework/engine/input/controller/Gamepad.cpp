//
// Created by loghin on 22.12.2021.
//

#include "Gamepad.hpp"

using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)

#include <Core.hpp>

auto __C_ENG_TYPE ( Gamepad ) :: toString () const noexcept -> String {
    static auto axesToString = []( float const * axes ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  __C_ENG_TYPE ( Gamepad ) :: axesCount; ++ i ) {
            asString += axes[i] + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    static auto buttonsToString = []( bool const * buttons ) noexcept -> String {
        String asString;
        for ( uint32 i = 0U; i <  __C_ENG_TYPE ( Gamepad ) :: buttonCount; ++ i ) {
            asString += :: toString ( buttons[i] ) + ", "_s;
        }

        return asString.removeSuffix (", ");
    };

    return __C_ENG_STRINGIFY ( __C_ENG_TYPE ( Gamepad ) ) " "
           "{ base = "          + this->__C_ENG_TYPE(Controller)::toString() +
           ", gamepadName = "   + this->gamepadName() +
           ", axes = "          + axesToString ( this->_axes ) +  // NOLINT(clion-misra-cpp2008-5-2-12)
           ", buttons = "       + buttonsToString ( this->_buttons ) +  // NOLINT(clion-misra-cpp2008-5-2-12)
           " }";
}
