//
// Created by loghin on 20.12.2021.
//

#include "KeyReleaseEvent.hpp"

namespace engine::io {

    KeyReleaseEvent :: KeyReleaseEvent (
            Window      const * pWindow,
            KeyType             key,
            KeyModifierFlags    modifierFlags
    ) noexcept :
            KeyEvent (pWindow, key, modifierFlags) {

    }

}
