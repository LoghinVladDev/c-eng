//
// Created by Vlad on 03/07/2020.
//

#include "KeyListener.h"

[[maybe_unused]] void KeyListener::keyPressed(uint16 keyCode) {
    this->keyModifier = (KeyModifier)glutGetModifiers();
}

[[maybe_unused]] void KeyListener::keyReleased(uint16 keyCode) {
    this->keyModifier = (KeyModifier)glutGetModifiers();
}
