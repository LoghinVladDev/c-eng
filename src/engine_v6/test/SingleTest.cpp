//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#include "Test.hpp"

namespace {
cds::UniquePointer <cds::Array <testing::Test*>> const tests =
    cds::makeUnique <cds::Array <testing::Test*>>();
} // namespace

namespace testing {
void _register(Test* test, char const* inst, char const* name) {
  (void) inst;
  (void) name;
  tests->pushBack(test);
}
} // namespace testing

auto main () noexcept -> int {
  for (auto const& e: *tests) {
    auto status = e->start();
    if (! status) {
      return 1;
    }
  }

  return 0;
}
