//
// Created by loghin on 20.12.2021.
//

#include "MouseScrollEvent.hpp"

namespace engine::io {

    MouseScrollEvent :: MouseScrollEvent (
            Window      const * pWindow,
            Point2D             position,
            Scale2DF            offset,
            KeyModifierFlags    keyModifierFlags
    ) noexcept :
            MouseEvent (pWindow, position),
            _offset (offset),
            _keyModifiers (keyModifierFlags) {

    }

}
