//
// Created by vladl on 08/07/2020.
//

#include "InputListener.h"

[[maybe_unused]] InputListener::KeyModifier InputListener::getKeyModifier() noexcept {
    return this->keyModifier;
}

[[maybe_unused]] void *InputListener::getParent() noexcept {
    return this->_parent;
}

[[maybe_unused]] void InputListener::updateKeyModifiers() noexcept {
    this->keyModifier = (KeyModifier)glutGetModifiers();
}
