//
// Created by loghin on 20.12.2021.
//

#include "KeyEvent.hpp"
#include <base/io/display/Window.hpp>

namespace engine::io {

    KeyEvent :: KeyEvent (
            Window      const * pWindow,
            KeyType             key,
            KeyModifierFlags    modifierFlags
    ) noexcept :
            Event (pWindow),
            _key (key),
            _modifierFlags (modifierFlags) {

    }

}
