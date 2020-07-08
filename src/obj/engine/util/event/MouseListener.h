//
// Created by vladl on 08/07/2020.
//

#ifndef ENG1_MOUSELISTENER_H
#define ENG1_MOUSELISTENER_H

#include "../defs/types.h"
#include "InputListener.h"

class MouseListener : public InputListener {
public:
    [[maybe_unused]] constexpr static uint16 MOUSE_BUTTON_LEFT   = GLUT_LEFT_BUTTON;
    [[maybe_unused]] constexpr static uint16 MOUSE_BUTTON_RIGHT  = GLUT_RIGHT_BUTTON;

    [[maybe_unused]] constexpr static uint16 MOUSE_STATE_UP      = GLUT_UP;
    [[maybe_unused]] constexpr static uint16 MOUSE_STATE_DOWN    = GLUT_DOWN;

    MouseListener() = default;

    [[maybe_unused]] virtual void buttonPressed(uint16, uint16, int, int) noexcept;
    [[maybe_unused]] virtual void moveEvent(int, int) noexcept;
};


#endif //ENG1_MOUSELISTENER_H
