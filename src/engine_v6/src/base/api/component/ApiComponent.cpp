//
// Created by Vlad-Andrei Loghin on 14.06.23.
//

#include "ApiComponent.hpp"
#include "src/engine_v6/src/base/api/Api.hpp"

using namespace engine;

ApiComponent::ApiComponent(engine::Api *parentApi) noexcept :
    Object(parentApi){

}

auto ApiComponent::api() noexcept -> Api* {
  return static_cast <Api*> (parent());
}

auto ApiComponent::api() const noexcept -> Api const* {
  return static_cast <Api const*> (parent());
}
