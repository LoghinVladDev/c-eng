//
// Created by loghin on 20.12.2021.
//

#include "MouseEvent.hpp"
#include <base/io/display/Window.hpp>

namespace engine::io {

    MouseEvent :: MouseEvent (
            Window  const * pWindow,
            Point2D         position
    ) noexcept :
            Event (pWindow),
            _position (position) {

    }

}
