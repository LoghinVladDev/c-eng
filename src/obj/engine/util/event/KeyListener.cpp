//
// Created by Vlad on 03/07/2020.
//

#include "KeyListener.h"

[[maybe_unused]] inline void KeyListener::keyPressed(uint16 keyCode) noexcept {
    InputListener::updateKeyModifiers();
}

[[maybe_unused]] inline void KeyListener::keyReleased(uint16 keyCode) noexcept {
    InputListener::updateKeyModifiers();
}
