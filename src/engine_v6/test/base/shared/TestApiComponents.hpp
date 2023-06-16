//
// Created by Vlad-Andrei Loghin on 16.06.23.
//

#ifndef C_ENG_TESTAPICOMPONENTS_HPP
#define C_ENG_TESTAPICOMPONENTS_HPP

#include <api/Api.hpp>

namespace testing {
template <typename C>
class TestApiOneComponent : public engine::Api {
protected:
  class Component : public C {
  public:
    explicit Component(engine::Api* p) noexcept : C(p) {}
  };

private:
  static inline Info info {.name = "generic"};
  [[no_unique_address]] Component c {this};

public:
  [[nodiscard]] auto apiInfo() const noexcept -> Info const& override {
    return info;
  }

  [[nodiscard]] auto getComponentList() noexcept -> cds::Array <engine::ApiComponent*> override {
    return {&c};
  }

  explicit TestApiOneComponent(engine::Engine* e) : engine::Api(e) {}
};
} // namespace

#endif //C_ENG_TESTAPICOMPONENTS_HPP
