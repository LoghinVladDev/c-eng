//
// Created by loghin on 20.12.2021.
//

#include "MouseEnterEvent.hpp"

namespace engine::io {

    MouseEnterEvent :: MouseEnterEvent (
            Window  const * pWindow,
            Point2D         position
    ) noexcept :
            MouseEvent (pWindow, position) {

    }

}
