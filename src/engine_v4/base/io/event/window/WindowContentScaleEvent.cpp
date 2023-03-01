//
// Created by loghin on 21.12.2021.
//

#include "WindowContentScaleEvent.hpp"

namespace engine::io {

    WindowContentScaleEvent :: WindowContentScaleEvent (
            Window  const * pWindow,
            Scale2DF        scale
    ) noexcept :
            WindowEvent(pWindow),
            _scale(scale) {

    }

}