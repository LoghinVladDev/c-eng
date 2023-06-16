#include "Engine.hpp"
#include "logging/Logger.hpp"
#include <glfw/Glfw.hpp>
#include <unix/Unix.hpp>
#include <fstream>

namespace {
  using engine::Engine;
  using engine::Logger;

  using engine::Glfw;
  using engine::Unix;
}

auto main (int argc, char const * const * ppArgv) noexcept -> int {
  std::ofstream lastLogEngine ("last_log_engine.txt");
  std::ofstream lastLogGlfw ("last_log_glfw.txt");
  auto& eLogger = Logger::getLogger(Engine::loggerName);
  auto& glfwLogger = Logger::getLogger(Glfw::loggerName);
  eLogger.outputs().pushBack(lastLogEngine);
  glfwLogger.outputs().pushBack(lastLogGlfw);

  Engine engine;
  engine.setPreInitHook([](Engine& e) {
    e.registerApi <Glfw>();
    e.registerApi <Unix>();
  });

  return engine.exec(argc, ppArgv);
}
