//
// Created by loghin on 21.12.2021.
//

#include "WindowMoveEvent.hpp"


namespace engine::io {

    WindowMoveEvent :: WindowMoveEvent (
            Window  const * pWindow,
            Point2D         position,
            Point2D         oldPosition
    ) noexcept :
            WindowEvent(pWindow),
            _position(position),
            _oldPosition(oldPosition) {

    }

}
