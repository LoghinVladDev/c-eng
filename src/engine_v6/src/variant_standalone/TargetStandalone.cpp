#include "Engine.hpp"
#include "logging/Logger.hpp"

namespace {
  using engine::Engine;
  using engine::Logger;
}

auto main (int argc, char const * const * ppARgv) noexcept -> int {

  Engine const engine;
  auto logger = Logger::getLogger();


  return 0;
}
