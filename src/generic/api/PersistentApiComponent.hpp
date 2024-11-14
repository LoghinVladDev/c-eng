//
// Created by loghin on 10/27/24.
//

#pragma once

#include "ApiComponent.hpp"
#include <generic/arch/Event.hpp>

namespace c_eng::generic::detail {
class PersistentApiObject {
public:
  virtual ~PersistentApiObject() noexcept = default;
};

class PersistentObjectCreatedEvent {
public:
  explicit PersistentObjectCreatedEvent(PersistentApiObject const* object) noexcept : _object{object} {}

  [[nodiscard]] auto object() const noexcept -> PersistentApiObject const* {
    return _object;
  }

private:
  PersistentApiObject const* _object {nullptr};
};

class PersistentObjectDestroyedEvent {
public:
  explicit PersistentObjectDestroyedEvent(PersistentApiObject const* object) noexcept : _object{object} {}

  [[nodiscard]] auto object() const noexcept -> PersistentApiObject const* {
    return _object;
  }

private:
  PersistentApiObject const* _object {nullptr};
};

class PersistenceApiComponent :
    public ApiComponent,
    public MultiEventNotifier<PersistentObjectCreatedEvent, PersistentObjectDestroyedEvent> {
public:
  ~PersistenceApiComponent() noexcept override = default;
};
} // namespace c_eng::generic::detail

namespace c_eng::generic {
using detail::PersistenceApiComponent;
using detail::PersistentApiObject;
using detail::PersistentObjectCreatedEvent;
using detail::PersistentObjectDestroyedEvent;
} // namespace c_eng::generic
