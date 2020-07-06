//
// Created by Vlad on 03/07/2020.
//

#include "KeyListener.h"

[[maybe_unused]] inline void KeyListener::keyPressed(uint16 keyCode) noexcept {
    this->keyModifier = (KeyModifier)glutGetModifiers();
}

[[maybe_unused]] inline void KeyListener::keyReleased(uint16 keyCode) noexcept {
    this->keyModifier = (KeyModifier)glutGetModifiers();
}

[[maybe_unused]] [[nodiscard]] inline KeyListener::KeyModifier KeyListener::getKeyModifier() noexcept {
    return this->keyModifier;
}

[[maybe_unused]] inline void* KeyListener::getParent () noexcept {
    return this->_parent;
}
