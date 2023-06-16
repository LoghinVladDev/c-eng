//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "core/Object.hpp"
#include <core/ResourceTracker.hpp>

namespace {
using engine::Object;
using engine::ResourceTracker;
}

TEST(ResouceTracker, track) {
  using IntResTracker = engine::ResourceTracker <int>;

  int x;
  int y;
  int z;

  x = 3;
  y = 2;
  z = 1;

  IntResTracker::tracker().track(&x);
  IntResTracker::tracker().track(&z);
  IntResTracker::tracker().track(&y);

  ASSERT_EQ(IntResTracker::tracker().instances().size(), 3);
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 1;}));
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 2;}));
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 3;}));
  ASSERT_FALSE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 4;}));

  IntResTracker::tracker().untrack(&y);
  ASSERT_EQ(IntResTracker::tracker().instances().size(), 2);
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 1;}));
  ASSERT_FALSE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 2;}));
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 3;}));

  IntResTracker::tracker().untrack(&x);
  ASSERT_EQ(IntResTracker::tracker().instances().size(), 1);
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 1;}));
  ASSERT_FALSE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 2;}));
  ASSERT_FALSE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 3;}));

  int t = 5;
  IntResTracker::tracker().track(&t);
  ASSERT_EQ(IntResTracker::tracker().instances().size(), 2);
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 1;}));
  ASSERT_FALSE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 2;}));
  ASSERT_FALSE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 3;}));
  ASSERT_TRUE(IntResTracker::tracker().instances().any([](auto* pInt){return *pInt == 5;}));

  IntResTracker::tracker().instances().clear();
  ASSERT_TRUE(IntResTracker::tracker().instances().empty());
}
