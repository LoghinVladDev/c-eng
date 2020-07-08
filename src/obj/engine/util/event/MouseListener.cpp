//
// Created by vladl on 08/07/2020.
//

#include "MouseListener.h"

[[maybe_unused]] inline void MouseListener::buttonPressed(uint16, uint16, int, int) noexcept {
    InputListener::updateKeyModifiers();
}

[[maybe_unused]] inline void MouseListener::moveEvent(int, int) noexcept {
    InputListener::updateKeyModifiers();
}
