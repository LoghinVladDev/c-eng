//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "core/Object.hpp"

namespace {
using engine::Object;
class Module : public Object {
public:
  explicit Module(Module* pMod = nullptr): Object(pMod) {}
};
}

TEST(ObjectHierarchy, Parent) {
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

TEST(ObjectHierarchy, ParentConst) {
  Module grandfather;
  Module father1(&grandfather);
  Module father2(&grandfather);
  Module const child1(&father1);
  Module const child2(&father1);
  Module const child3(&father2);

  ASSERT_EQ(child1.parent(), child2.parent());
  ASSERT_NE(child3.parent(), child2.parent());

  ASSERT_EQ(father1.parent(), father2.parent());
  ASSERT_EQ(grandfather.parent(), nullptr);

  ASSERT_EQ(child1.parent()->parent(), child2.parent()->parent());
  ASSERT_EQ(child1.parent()->parent(), child3.parent()->parent());
}

TEST(ObjectHierarchy, SetParent) {
  Module grdf;
  Module f1;
  Module f2(&grdf);
  Module c1(&f1);
  Module c2;
  Module c3;

  f1.setParent(&grdf);
  c2.setParent(&f2);
  c3.setParent(&f2);

  ASSERT_EQ(f1.parent(), f2.parent());
  ASSERT_EQ(f1.parent(), &grdf);

  ASSERT_EQ(c1.parent(), &f1);
  ASSERT_EQ(c2.parent(), c3.parent());
  ASSERT_EQ(c2.parent(), &f2);
}
