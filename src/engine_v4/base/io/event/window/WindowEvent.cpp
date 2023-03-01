//
// Created by loghin on 21.12.2021.
//

#include "WindowEvent.hpp"

#include <base/io/display/Window.hpp>

namespace engine::io {

    WindowEvent :: WindowEvent (Window const * pWindow) noexcept :
            Event(pWindow) {

    }

}