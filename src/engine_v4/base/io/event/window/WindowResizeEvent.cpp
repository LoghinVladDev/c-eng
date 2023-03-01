//
// Created by loghin on 20.12.2021.
//

#include "WindowResizeEvent.hpp"

namespace engine::io {

    WindowResizeEvent :: WindowResizeEvent (
            Window  const * pWindow,
            Size2D          size,
            Size2D          oldSize
    ) noexcept :
            WindowEvent(pWindow),
            _size(size),
            _oldSize(oldSize) {

    }

}
