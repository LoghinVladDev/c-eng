//
// Created by Vlad-Andrei Loghin on 16.06.23.
//

#include "../../shared/TimeoutTest.hpp"
#include "../../Test.hpp"

TEST(TimeoutTest, positive) {
  ASSERT_TRUE(timeoutTest([]{
    usleep(1000);
  }, 100));
}

TEST(TimeoutTest, negative) {
  ASSERT_FALSE(timeoutTest([]{
    usleep(100000000);
  }, 10));
}
