//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#include "UnixSystemApiComponent.hpp"
#include <unix/Unix.hpp>
#include <core/ResourceTracker.hpp>

using namespace engine;
using namespace cds;

namespace {
class UnixSystemApiComponentTracker : public ResourceTracker <UnixSystemApiComponent> {};

auto signalCallback(int signalValue) noexcept -> void {
  UnixSystemApiComponentTracker::tracker().instances().forEach([signalValue](auto* pComponent){
    if (signalValue == SIGTERM || signalValue == SIGHUP) {
      pComponent->requestShutdown();
    }
  });
}
} // namespace

UnixSystemApiComponent::UnixSystemApiComponent(Unix* pParentApi) noexcept :
    SystemApiComponent(pParentApi) {

  UnixSystemApiComponentTracker::tracker().track(this);
  signal (SIGTERM, &signalCallback);
  signal (SIGHUP, &signalCallback);
}

UnixSystemApiComponent::~UnixSystemApiComponent() noexcept {
  try {
    UnixSystemApiComponentTracker::tracker().untrack(this);
  } catch (...) {
    std::terminate();
  }
}
