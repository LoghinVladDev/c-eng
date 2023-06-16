//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "src/engine_v6/src/base/Engine.hpp"
#include "src/engine_v6/src/api/unix/Unix.hpp"
#include "src/engine_v6/src/api/unix/component/UnixSystemApiComponent.hpp"
#include "../../../shared/CrashTest.hpp"
#include <csignal>

namespace {
using namespace cds;
using namespace cds::literals;
using engine::Engine;
using engine::Api;
using engine::Unix;
using engine::UnixSystemApiComponent;
}

TEST(UnixSystemApiComponent, signalledShutdownRequest) {

  auto r = RunResult {RunStatus::Signalled, SIGTERM};
  auto e = crashTest([]{
    Engine e1;
    e1.registerApi<Unix>();
    e1.exec(0, nullptr);
  },[](pid_t pid){
    kill(pid, SIGTERM);
  });

  ASSERT_EQ(r, e);
}

TEST(UnixSystemApiComponent, signalledShutdownRequest2) {
  auto r1 = RunResult {RunStatus::Exited, 0};
  auto e = crashTest([](){
    kill(getppid(), SIGHUP);
  },[](pid_t p){
    (void) p;
    Engine e1;
    e1.registerApi<Unix>();
    e1.exec(0, nullptr);
  });

  ASSERT_EQ(r1, e);
}

TEST(UnixSystemApiComponent, signalledShutdownRequest3) {
  auto r1 = RunResult {RunStatus::Exited, 0};
  auto e = crashTest([](){
    kill(getppid(), SIGTERM);
  },[](pid_t p){
    (void) p;
    Engine e1;
    e1.registerApi<Unix>();
    e1.exec(0, nullptr);
  });

  ASSERT_EQ(r1, e);
}

TEST(UnixSystemApiComponent, componentWithoutApi) {
  auto r1 = RunResult {RunStatus::Signalled, SIGABRT};
  UnixSystemApiComponent c(nullptr);
  ASSERT_EQ(crashTest([&c]{
    c.requestShutdown();
  }), r1);

  Unix api (nullptr);
  UnixSystemApiComponent c2(&api);
  ASSERT_EQ(crashTest([&c2]{
    c2.requestShutdown();
  }), r1);
}
