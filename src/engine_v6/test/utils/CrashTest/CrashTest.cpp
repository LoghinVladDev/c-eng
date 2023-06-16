//
// Created by Vlad-Andrei Loghin on 16.06.23.
//

#include "../../Test.hpp"
#include "../../shared/CrashTest.hpp"
#include <csignal>

namespace {
using enum testing::RunStatus;
}

TEST(CrashTest, positive) {

  auto r1 = RunResult{Signalled, SIGTERM};
  ASSERT_EQ(
    crashTest(
        []{while(true){}},
        [](pid_t pid) {
          kill(pid, SIGTERM);
        }
    ), r1
  );

  auto r2 = RunResult{Exited, 5};
  ASSERT_EQ(
      crashTest(
          []{exit(5);}
      ), r2
  );
}

TEST(CrashTest, negative) {
  auto r1 = RunResult{Signalled, SIGABRT};

  ASSERT_EQ(
      crashTest(
          []{assert(false);}
      ),
      r1
  );

  auto r2 = RunResult{Signalled, SIGABRT};
  ASSERT_EQ(
      crashTest(
          []{*((int volatile*)0x100) = 5;}
      ), r2
  );
}

TEST(CrashTest, ResultComp) {
  RunResult a {Signalled, 0};
  RunResult b {Signalled, 1};
  RunResult c {Unknown, 0};
  RunResult d {Unknown, 1};

  ASSERT_EQ(a, a);
  ASSERT_NE(a, b);
  ASSERT_NE(a, c);
  ASSERT_NE(a, d);
}
