#include <Engine.hpp>

using namespace engine;

auto Engine::setPreInitHook(cds::Function<void(Engine&)> hook) noexcept -> Engine& {
  assert(!hook.empty() && "Hook should be non-null");
  preInitHook = std::move(hook);
  return *this;
}

auto Engine::setPostInitHook(cds::Function<void(Engine&)> hook) noexcept -> Engine& {
  assert(!hook.empty() && "Hook should be non-null");
  postInitHook = std::move(hook);
  return *this;
}

auto Engine::setPreUpdateHook(cds::Function<void(Engine&)> hook) noexcept -> Engine& {
  assert(!hook.empty() && "Hook should be non-null");
  preUpdateHook = std::move(hook);
  return *this;
}

auto Engine::setPostUpdateHook(cds::Function<void(Engine&)> hook) noexcept -> Engine& {
  assert(!hook.empty() && "Hook should be non-null");
  postUpdateHook = std::move(hook);
  return *this;
}

auto Engine::setPreShutdownHook(cds::Function<void(Engine&)> hook) noexcept -> Engine& {
  assert(!hook.empty() && "Hook should be non-null");
  preShutdownHook = std::move(hook);
  return *this;
}

auto Engine::setPostShutdownHook(cds::Function<void(Engine&)> hook) noexcept -> Engine& {
  assert(!hook.empty() && "Hook should be non-null");
  postShutdownHook = std::move(hook);
  return *this;
}

auto Engine::exec(int argc, char const* const* argv) noexcept -> int {
  (void) argc;
  (void) argv;

  try {

    logger.setDefaultLevel(Logger::Info);
    logger() << "Engine Startup";

    logger() << "Calling Pre-Init Hook";
    preInitHook(*this);
    logger() << "Calling Init";
    init();
    logger() << "Calling Post-Init Hook";
    postInitHook(*this);

    logger() << "Entering Main Loop";
    mainLoop();

    logger() << "Calling Shutdown";
    shutdown();
    logger() << "Calling Post-Shutdown Hook";
    postShutdownHook(*this);

  } catch (cds::Exception const& irrecoverableError) {
    logger() << Logger::Error << "Irrecoverable Exception: " << irrecoverableError.message() << "\n";
    return 1;
  }

  return 0;
}

auto Engine::mainLoop() noexcept(false) -> void {
  while (!shutdownRequested()) {
    preUpdateHook(*this);
    update();
    postUpdateHook(*this);

    if (shutdownRequested()) {
      logger() << "Engine Shutting Down due to Shutdown Request";
      logger() << "Calling Pre-Shutdown Hook";
      preShutdownHook(*this);

      if (!shutdownRequested()) {
        logger() << "Shutdown Cancelled";
      }
    }
  }
}

auto Engine::init() noexcept(false) -> void {

}

auto Engine::update() noexcept(false) -> void {

}

auto Engine::shutdown() noexcept(false) -> void {

}
