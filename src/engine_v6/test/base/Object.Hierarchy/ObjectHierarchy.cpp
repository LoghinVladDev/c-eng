//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "core/Object.hpp"

namespace {
using engine::Object;
}

TEST(ObjectHierarchy, Parent) {
  class Module : public Object {
  public:
    explicit Module(Module* pMod = nullptr): Object(pMod) {}
  };

  Module grandfather;
  Module father1(&grandfather);
  Module father2(&grandfather);
  Module child1(&father1);
  Module child2(&father1);
  Module child3(&father2);

  ASSERT_EQ(child1.parent(), child2.parent());
  ASSERT_NE(child3.parent(), child2.parent());

  ASSERT_EQ(father1.parent(), father2.parent());
  ASSERT_EQ(grandfather.parent(), nullptr);

  ASSERT_EQ(child1.parent()->parent(), child2.parent()->parent());
  ASSERT_EQ(child1.parent()->parent(), child3.parent()->parent());
}
