//
// Created by loghin on 30/04/23.
//

#include "Test.hpp"
#include "logging/Logger.hpp"
#include <chrono>
#include <string>
#include <CDS/Long>
#include <CDS/threading/Thread>
#include "../shared/LoggerShared.hpp"
#include <Engine.hpp>

using namespace engine;

auto timeoutTest(auto fn, int timeMs) {
  auto status = false;
  auto timeoutTh = cds::Runnable([&fn, &status]{
    fn();
    status = true;
  });
  timeoutTh.start();
  usleep(timeMs * 1000);
  if (!status) { timeoutTh.kill(); }
  else { timeoutTh.join(); }
  return status;
}

TEST(Engine, shutdownScenarios) {
  ASSERT_TRUE(timeoutTest([]{
    auto engine1 = Engine();
    engine1.setPreInitHook([](Engine& e){e.requestShutdown();});
    (void) engine1.exec(0, nullptr);
  }, 10));

  ASSERT_TRUE(timeoutTest([]{
    auto engine1 = Engine();
    engine1.setPostInitHook([](Engine& e){e.requestShutdown();});
    (void) engine1.exec(0, nullptr);
  }, 10));

  ASSERT_TRUE(timeoutTest([]{
    auto engine1 = Engine();
    engine1.setPreUpdateHook([](Engine& e){e.requestShutdown();});
    (void) engine1.exec(0, nullptr);
  }, 10));

  ASSERT_TRUE(timeoutTest([]{
    auto engine1 = Engine();
    engine1.setPostUpdateHook([](Engine& e){e.requestShutdown();});
    (void) engine1.exec(0, nullptr);
  }, 10));

  ASSERT_TRUE(timeoutTest([]{
    auto engine1 = Engine();
    auto th = cds::Runnable([&engine1]{
      engine1.exec(0, nullptr);
    });

    th.start();
    engine1.requestShutdown();
    th.join();
  }, 10));
}

TEST(Engine, hookExecCount) {
  auto engine = Engine();

  int preI = 0;
  int postI = 0;
  int preU = 0;
  int postU = 0;
  int preS = 0;
  int postS = 0;

  engine.setPreInitHook([&preI](Engine const& e){(void) e; ++preI;});
  engine.setPostInitHook([&postI](Engine const& e){(void) e; ++postI;});
  engine.setPreUpdateHook([&preU](Engine const& e){(void) e; ++preU;});
  engine.setPostUpdateHook([&postU](Engine& e){++postU; e.requestShutdown();});
  engine.setPreShutdownHook([&preS](Engine const& e){(void) e; ++preS;});
  engine.setPostShutdownHook([&postS](Engine const& e){(void) e; ++postS;});

  engine.exec(0, nullptr);
  ASSERT_EQ(preI, 1);
  ASSERT_EQ(preU, 1);
  ASSERT_EQ(preS, 1);
  ASSERT_EQ(postI, 1);
  ASSERT_EQ(postU, 1);
  ASSERT_EQ(postS, 1);

  auto engine2 = Engine();
  preU = 0;
  postU = 0;

  engine2.setPreUpdateHook([&preU](Engine& e){
    ++ preU;
    if (preU == 5) {
      e.requestShutdown();
    }
  });

  engine2.setPostUpdateHook([&postU](Engine const& e) {
    (void) e;
    ++ postU;
  });
  engine2.exec(0, nullptr);

  ASSERT_EQ(preU, 5);
  ASSERT_EQ(postU, 5);
}

TEST(Engine, shutdownCancellation) {
  auto e1 = Engine();
  int reqCnt = 0;

  e1.setPostUpdateHook([](Engine& e){e.requestShutdown();});
  e1.setPreShutdownHook([&reqCnt](Engine& e){++reqCnt; if(reqCnt == 3){e.cancelShutdownRequest();}});
  ASSERT_TRUE(timeoutTest([&e1]{e1.exec(0, nullptr);}, 10));
}

TEST(Engine, logger) {
  auto e = Engine();
  auto &l = Logger::getLogger(Engine::loggerName);
  std::stringstream sb;

  l.outputs().clear();
  l.outputs().insert(sb);

  ASSERT_TRUE(timeoutTest([&e]{
    e.setPostUpdateHook([](Engine &e1) { e1.requestShutdown(); });
    e.exec(0, nullptr);
  }, 10));
  ASSERT_TRUE(contains(sb, "Engine Startup"));
  ASSERT_TRUE(contains(sb, "Calling Pre-Init Hook"));
  ASSERT_TRUE(contains(sb, "Calling Init"));
  ASSERT_TRUE(contains(sb, "Calling Post-Init Hook"));
  ASSERT_TRUE(contains(sb, "Entering Main Loop"));
  ASSERT_TRUE(contains(sb, "Engine Shutting Down due to Shutdown Request"));
  ASSERT_TRUE(contains(sb, "Calling Pre-Shutdown Hook"));
  ASSERT_TRUE(contains(sb, "Calling Shutdown"));
  ASSERT_TRUE(contains(sb, "Calling Post-Shutdown Hook"));
}
