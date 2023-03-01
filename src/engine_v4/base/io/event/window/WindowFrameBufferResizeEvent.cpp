//
// Created by loghin on 21.12.2021.
//

#include "WindowFrameBufferResizeEvent.hpp"

namespace engine::io {

    WindowFrameBufferResizeEvent :: WindowFrameBufferResizeEvent (
            Window  const * pWindow,
            Size2D          size,
            Size2D          oldSize
    ) noexcept :
            WindowEvent(pWindow),
            _size(size),
            _oldSize(oldSize) {

    }

}
