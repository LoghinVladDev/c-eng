//
// Created by Vlad on 03/07/2020.
//

#include "KeyListener.h"
#include <cstdio>

[[maybe_unused]] inline void engine::KeyListener::keyPressed(int key, int scanCode, engine::KeyListener::KeyModifier mods) noexcept {
    std::fprintf(stdout, "[Key pressed] : { key = %d, scancode = %d, mods = %d }\n", key, scanCode, mods);
}

[[maybe_unused]] inline void engine::KeyListener::keyReleased(int key, int scanCode, engine::KeyListener::KeyModifier mods) noexcept {
    std::fprintf(stdout, "[Key released] : { key = %d, scancode = %d, mods = %d }\n", key, scanCode, mods);
}

[[maybe_unused]] inline void engine::KeyListener::keyHeld(int key, int scanCode, engine::KeyListener::KeyModifier mods) noexcept {
    std::fprintf(stdout, "[Key held] : { key = %d, scancode = %d, mods = %d }\n", key, scanCode, mods);
}