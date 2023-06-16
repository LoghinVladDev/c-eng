#include <Engine.hpp>

using namespace engine;
using namespace cds;

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
    logger() << "Engine Startup" << std::endl;

    logger() << "Calling Pre-Init Hook" << std::endl;
    preInitHook(*this);
    logger() << "Calling Init" << std::endl;
    init();
    logger() << "Calling Post-Init Hook" << std::endl;
    postInitHook(*this);

    logger() << "Entering Main Loop" << std::endl;
    mainLoop();

    logger() << "Calling Shutdown" << std::endl;
    shutdown();
    logger() << "Calling Post-Shutdown Hook" << std::endl;
    postShutdownHook(*this);
  } catch (cds::Exception const& irrecoverableError) {
    logger() << Logger::Error << "Irrecoverable Exception: " << irrecoverableError.message() << std::endl;
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
      logger() << "Engine Shutting Down due to Shutdown Request" << std::endl;
      logger() << "Calling Pre-Shutdown Hook" << std::endl;
      preShutdownHook(*this);

      if (!shutdownRequested()) {
        logger() << "Shutdown Cancelled" << std::endl;
      }
    }
  }
}

auto Engine::init() noexcept(false) -> void {
  // to be added
}

auto Engine::update() noexcept(false) -> void {
  // to be added
}

auto Engine::shutdown() noexcept(false) -> void {
  // to be added
}

auto Engine::apiList() const noexcept -> Array<Api const*> {
  return {apis.begin(), apis.end()};
}
