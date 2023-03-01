//
// Created by loghin on 20.12.2021.
//

#include "MouseMoveEvent.hpp"

namespace engine::io {

    MouseMoveEvent :: MouseMoveEvent (
            Window  const * pWindow,
            Point2D         position,
            Point2D         oldPosition
    ) noexcept :
            MouseEvent (pWindow, position),
            _oldPosition (oldPosition) {

    }

}
