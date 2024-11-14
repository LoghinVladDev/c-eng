//
// Created by loghin on 10/25/24.
//

#pragma once

#include <cds/collection/Vector>
#include <generic/api/Api.hpp>
#include <generic/api/EventApiComponent.hpp>
#include <generic/api/PersistentApiComponent.hpp>

namespace c_eng::generic::detail {
class Engine : public MultiEventSubscriber<PersistentObjectCreatedEvent, PersistentObjectDestroyedEvent> {
public:
  explicit Engine(Vector<Api const*>&& apis);

  auto notify(PersistentObjectCreatedEvent& event) noexcept -> void override;
  auto notify(PersistentObjectDestroyedEvent& event) noexcept -> void override;
  [[nodiscard]] auto run() noexcept -> int;

private:
  Vector<Api const*> _apis;
  Vector<EventPollingApiComponent*> _pollingComponents;
  Vector<PersistentApiObject const*> _persistentComponents;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::Engine;
} // namespace c_eng::generic
