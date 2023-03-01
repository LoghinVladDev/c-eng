//
// Created by loghin on 21.12.2021.
//

#include "WindowRestoreEvent.hpp"


namespace engine::io {

    WindowRestoreEvent :: WindowRestoreEvent (Window const * pWindow) noexcept :
            WindowEvent(pWindow) {

    }

}