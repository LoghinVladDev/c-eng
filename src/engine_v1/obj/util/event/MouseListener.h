//
// Created by vladl on 10/07/2020.
//

#ifndef ENG1_MOUSELISTENER_H
#define ENG1_MOUSELISTENER_H

#include "InputListener.h"

namespace engine {

    class MouseListener : public InputListener {
    public:
        constexpr static bool MOUSE_PRESSED     = GLFW_PRESS;
        constexpr static bool MOUSE_RELEASED    = GLFW_PRESS;
    protected:
    public:
        virtual void mouseMoved(double xPos, double yPos) noexcept;
        virtual void mouseClicked(int button, int mods) noexcept;
        virtual void mouseScrolled(double xOffset, double yOffset) noexcept;
        virtual void mouseReleased(int button, int mods) noexcept;
    };

}

#endif //ENG1_MOUSELISTENER_H
