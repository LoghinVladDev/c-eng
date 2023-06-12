#pragma once

#include "core/Object.hpp"
#include <CDS/Function>
#include <logging/Logger.hpp>

namespace engine {
class Engine : public Object {
public:
  constexpr static auto const loggerName = "EngineLogger";

  using Object::Object;

  auto setPreInitHook (cds::Function <void(Engine&)> hook) noexcept -> Engine&;
  auto setPostInitHook (cds::Function <void(Engine&)> hook) noexcept -> Engine&;
  auto setPreUpdateHook (cds::Function <void(Engine&)> hook) noexcept -> Engine&;
  auto setPostUpdateHook (cds::Function <void(Engine&)> hook) noexcept -> Engine&;
  auto setPreShutdownHook (cds::Function <void(Engine&)> hook) noexcept -> Engine&;
  auto setPostShutdownHook (cds::Function <void(Engine&)> hook) noexcept -> Engine&;

  auto exec(int argc, char const* const* argv) noexcept -> int;

  auto requestShutdown() noexcept -> Engine& {
    logger() << "Shutdown Requested";
    shutdownRequestStatus = true;
    return *this;
  }

  auto cancelShutdownRequest() noexcept -> Engine& {
    logger() << "Cancelling Shutdown Request";
    shutdownRequestStatus = false;
    return *this;
  }

private:
  auto init() noexcept(false) -> void;
  auto update() noexcept(false) -> void;
  auto shutdown() noexcept(false) -> void;
  auto mainLoop() noexcept(false) -> void;

  [[nodiscard]] constexpr auto shutdownRequested() const noexcept -> bool {
    return shutdownRequestStatus;
  }

  cds::Function <void(Engine&)> preInitHook = [](Engine const& engine){(void) engine;};
  cds::Function <void(Engine&)> postInitHook = [](Engine const& engine){(void) engine;};
  cds::Function <void(Engine&)> preUpdateHook = [](Engine const& engine){(void) engine;};
  cds::Function <void(Engine&)> postUpdateHook = [](Engine const& engine){(void) engine;};
  cds::Function <void(Engine&)> preShutdownHook = [](Engine const& engine){(void) engine;};
  cds::Function <void(Engine&)> postShutdownHook = [](Engine const& engine){(void) engine;};

  bool shutdownRequestStatus {false};

  static inline Logger& logger = Logger::getLogger(loggerName);
};
}
