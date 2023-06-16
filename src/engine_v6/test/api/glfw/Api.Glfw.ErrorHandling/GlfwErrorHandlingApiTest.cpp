//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "src/engine_v6/src/api/glfw/Glfw.hpp"
#include "src/engine_v6/src/base/Engine.hpp"
#include "../../../base/shared/LoggerShared.hpp"
#include <GLFW/glfw3.h>
#include "../../../shared/CrashTest.hpp"

namespace  {
using engine::Glfw;
using engine::Engine;
using engine::Logger;
using engine::Api;
using namespace cds;
using namespace cds::literals;
}

extern "C" {
extern void simulateInvalid();
extern void mockMonitorCallback();
}

TEST(GlfwErrorHandlingApi, logging) {
  std::stringstream sb;
  auto e = makeUnique <Engine>();
  Logger& l = Logger::getLogger(Glfw::loggerName);
  l.outputs() = {sb};
  e->registerApi<Glfw>();

  ASSERT_TRUE(contains(sb, "Initializing GLFW"));
  ASSERT_TRUE(contains(sb, "GLFW Initialized Successfully"));

  e = nullptr;

  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_NOT_INITIALIZED, testDesc1"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_NO_CURRENT_CONTEXT, testDesc2"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_INVALID_ENUM, testDesc3"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_INVALID_VALUE, testDesc4"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_OUT_OF_MEMORY, testDesc5"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_API_UNAVAILABLE, testDesc6"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_VERSION_UNAVAILABLE, testDesc7"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_PLATFORM_ERROR, testDesc8"));
  ASSERT_TRUE(contains(sb, "Glfw Error: GLFW_FORMAT_UNAVAILABLE, testDesc9"));

  std::stringstream().swap(sb);
  e = makeUnique <Engine>();
  try {
    e->registerApi<Glfw>();
  } catch (RuntimeException const& e) {
    ASSERT_TRUE(contains(e.message().toStdString(), "Glfw Exception: "));
    ASSERT_TRUE(true);
  } catch (...) {
    ASSERT_TRUE(false);
  }
  ASSERT_TRUE(contains(sb, "Initializing GLFW"));
  ASSERT_FALSE(contains(sb, "GLFW Initialized Successfully"));

  e = nullptr;

  e = makeUnique<Engine>();
  auto r = RunResult{RunStatus::Signalled, SIGABRT};
  ASSERT_EQ(
      crashTest([&e] {
        /// returns invalid code at second init
        e->registerApi<Glfw>();
        simulateInvalid();
      }),
      r
  );

  mockMonitorCallback();
}
