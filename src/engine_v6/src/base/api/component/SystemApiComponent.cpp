//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#include "SystemApiComponent.hpp"
#include <api/Api.hpp>
#include <Engine.hpp>

using namespace engine;

auto SystemApiComponent::requestShutdown() noexcept -> void {
  assert(api() != nullptr && "Should ONLY be called from a component inside of an API");
  assert(api()->engine() != nullptr && "API of the component MUST be registered to an Engine before this call");
  api()->engine()->requestShutdown();
}
