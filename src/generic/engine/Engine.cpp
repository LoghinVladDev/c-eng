//
// Created by loghin on 10/25/24.
//

#include "Engine.hpp"

#include <generic/lang/Range.hpp>
#include <generic/lang/Semantic.hpp>

namespace c_eng::generic::detail {
using cds::impl::mv;

Engine::Engine(Vector<Api const*>&& apis) :
    _apis{mv(apis)},
    _pollingComponents{
        _apis | project(&Api::components)
              | flatten()
              | project(dynCast<EventPollingApiComponent>)
              | filter(notNull)
    } {
  _apis | project(&Api::components)
      | flatten()
      | project(dynCast<PersistenceApiComponent>)
      | filter(notNull)
      | forEach([this](auto* obj) {
        obj->subscribe(this);
      });
}

auto Engine::notify(PersistentObjectCreatedEvent& event) noexcept -> void {
  _persistentComponents.emplaceBack(event.object());
}

auto Engine::notify(PersistentObjectDestroyedEvent& event) noexcept -> void {
  _persistentComponents.remove(_persistentComponents.findFirst(event.object()));
}

auto Engine::run(FunctionRef<Expected<void, int>()> onUpdate) noexcept -> int {
  while (!_persistentComponents.empty()) {
    for (auto* component : _pollingComponents) {
      component->poll();
      if (auto const result = onUpdate(); !result) {
        return result.error();
      }
    }
  }

  return 0;
}

} // namespace c_eng::generic::detail
