//
// Created by vladl on 10/07/2020.
//

#include "MouseListener.h"
#include <cstdio>

void engine::MouseListener::mouseMoved(double xPos, double yPos) noexcept {
    std::fprintf(stdout, "[Mouse moved] : { x = %lf, y = %lf }\n", xPos, yPos);
}

void engine::MouseListener::mouseClicked(int button, int mods) noexcept {
    std::fprintf(stdout, "[Mouse clicked] : { button = %d, mods = %d }\n", button, mods);
}

void engine::MouseListener::mouseReleased(int button, int mods) noexcept {
    std::fprintf(stdout, "[Mouse released] : { button = %d, mods = %d }\n", button, mods);
}

void engine::MouseListener::mouseScrolled(double xOffset, double yOffset) noexcept {
    std::fprintf(stdout, "[Mouse scrolled] : { xOff = %d, yOff = %d }\n", xOffset, yOffset);
}
