//
// Created by loghin on 21.12.2021.
//

#include "WindowRefreshRequestEvent.hpp"


namespace engine::io {

    WindowRefreshRequestEvent :: WindowRefreshRequestEvent (Window const * pWindow) noexcept :
            WindowEvent(pWindow) {

    }

}