//
// Created by loghin on 20.12.2021.
//

#include "MouseLeaveEvent.hpp"

namespace engine::io {

    MouseLeaveEvent :: MouseLeaveEvent (
            Window  const * pWindow,
            Point2D         position
    ) noexcept :
            MouseEvent (pWindow, position) {

    }

}
