//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include <Engine.hpp>
#include <api/component/MouseApiComponent.hpp>
#include "../shared/TestApiComponents.hpp"

namespace {
using testing::TestApiOneComponent;
using engine::Engine;
using engine::Api;
using engine::ApiComponent;
using engine::MouseApiComponent;
using namespace cds;
using namespace cds::literals;

class TestApi : public TestApiOneComponent<MouseApiComponent> {
  using TestApiOneComponent::TestApiOneComponent;
};
}

TEST(MouseApiComponent, type) {
  Engine e;
  e.registerApi<TestApi>();
  ASSERT_EQ(e.apiList()[0]->components()[0]->type(), ApiComponent::Type::Mouse);
}
