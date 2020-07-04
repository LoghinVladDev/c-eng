//
// Created by Vlad on 03/07/2020.
//

#include "Engine.h"

Engine::Engine() noexcept = default;

/**
 * might become problematic
 */
Engine::~Engine() noexcept {
    this->mainWindow.~Window();
}

[[maybe_unused]] void Engine::start(int argc, char** argv) noexcept {
    this->mainWindow.run(argc, argv);
}
