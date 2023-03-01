//
// Created by loghin on 20.12.2021.
//

#include "MousePressEvent.hpp"

namespace engine::io {

    MousePressEvent :: MousePressEvent (
            Window      const * pWindow,
            Point2D             position,
            MouseButtonType     button,
            KeyModifierFlags    modifierFlags
    ) noexcept :
            MouseEvent (pWindow, position),
            _button (button),
            _keyModifiers (modifierFlags) {

    }

}