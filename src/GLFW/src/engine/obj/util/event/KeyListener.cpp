//
// Created by Vlad on 03/07/2020.
//

#include "KeyListener.h"
#include <cstdio>

[[maybe_unused]] inline void KeyListener::keyPressed(int key, int scanCode, int mods) noexcept {
    std::fprintf(stdout, "[Key pressed] : { key = %d, scancode = %d, mods = %d }", key, scanCode, mods);
}

[[maybe_unused]] inline void KeyListener::keyReleased(int key, int scanCode, int mods) noexcept {
    std::fprintf(stdout, "[Key released] : { key = %d, scancode = %d, mods = %d }", key, scanCode, mods);
}
