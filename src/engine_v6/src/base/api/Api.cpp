//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#include "Api.hpp"
#include <Engine.hpp>

using namespace engine;

auto Api::getComponentList() noexcept -> cds::Array <ApiComponent*> {
  return {};
}

auto Api::components() noexcept -> cds::Array <ApiComponent*> {
  return getComponentList();
}

auto Api::components() const noexcept -> cds::Array <ApiComponent const*> {
  auto _components = const_cast <Api*> (this)->getComponentList();
  return {_components.begin(), _components.end()};
}

auto Api::engine() noexcept -> Engine* {
  return static_cast<Engine*>(parent());
}

auto Api::engine() const noexcept -> Engine const* {
  return static_cast<Engine const*>(parent());
}

Api::Api(Engine* pParent) noexcept : Object(pParent) {}
