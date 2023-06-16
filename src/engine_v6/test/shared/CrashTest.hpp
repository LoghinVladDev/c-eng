//
// Created by Vlad-Andrei Loghin on 16.06.23.
//

#ifndef C_ENG_CRASHTEST_HPP
#define C_ENG_CRASHTEST_HPP

#include <CDS/exception/RuntimeException>
#include <unistd.h>

namespace testing {
enum class RunStatus {
  Exited,
  Stopped,
  Signalled,
  Unknown
};

struct RunResult {
  RunStatus status;
  int value;

  [[nodiscard]] bool operator == (RunResult const& r) const noexcept = default;
};

RunResult crashTest(auto fnToCrash, auto fnToControl) {
  using enum RunStatus;
  pid_t pid = fork();
  if (pid == 0) {
    fnToCrash();
    exit(0);
  } else if (pid > 0) {
    fnToControl(pid);
    int retCode;
    waitpid(pid, &retCode, 0);

    if (WIFSTOPPED(retCode)) {
      return {Stopped, WSTOPSIG(retCode)};
    }

    if (WIFSIGNALED(retCode)) {
      return {Signalled, WTERMSIG(retCode)};
    }

    if (WIFEXITED(retCode)) {
      return {Exited, WEXITSTATUS(retCode)};
    }

    return {Unknown, -1};
  } else {
    throw cds::RuntimeException("Invalid Fork");
  }
}

auto crashTest (auto fnToCrash) {
  return crashTest(fnToCrash, [](pid_t pid){(void) pid;});
}
}

#endif //C_ENG_CRASHTEST_HPP
