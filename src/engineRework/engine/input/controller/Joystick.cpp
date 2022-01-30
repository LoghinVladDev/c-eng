//
// Created by loghin on 22.12.2021.
//

#include "Joystick.hpp"

#include <Core.hpp>


using namespace cds; // NOLINT(clion-misra-cpp2008-7-3-4)
using namespace engine; // NOLINT(clion-misra-cpp2008-7-3-4)


#define C_ENG_MAP_START     CLASS ( Joystick, ENGINE_PARENT ( Controller ) )
#include <ObjectMapping.hpp>

Self :: Destructor () noexcept {
    delete[] this->_axes;
    delete[] this->_buttons;
    delete[] this->_hats;
}

auto Self :: toString () const noexcept -> String {
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

    return __C_ENG_STRINGIFY ( Self ) " "
           "{ base = "      + this-> Parent :: toString() +
           ", axes = "      + axesToString ( this->_axes, this->_axisCount ) +
           ", buttons = "   + buttonsToString ( this->_buttons, this->_buttonCount ) +
           ", hats = "      + hatsToString ( this->_hats, this->_hatCount ) +
           " }";
}