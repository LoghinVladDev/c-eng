//
// Created by loghin on 20.12.2021.
//

#include "MouseReleaseEvent.hpp"

namespace engine::io {

    MouseReleaseEvent :: MouseReleaseEvent (
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
