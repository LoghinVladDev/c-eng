//
// Created by loghin on 20.12.2021.
//

#include "KeyPressEvent.hpp"

namespace engine::io {

    KeyPressEvent :: KeyPressEvent (
            Window      const * pWindow,
            KeyType             key,
            KeyModifierFlags    modifierFlags
    ) noexcept :
            KeyEvent (pWindow, key, modifierFlags) {

    }

}