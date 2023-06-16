//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "src/engine_v6/src/api/glfw/Glfw.hpp"
#include "src/engine_v6/src/base/Engine.hpp"
#include "../../../base/shared/LoggerShared.hpp"
#include <GLFW/glfw3.h>

namespace  {
using engine::Glfw;
using engine::Engine;
using engine::Logger;
using engine::Api;
using namespace cds;
using namespace cds::literals;
}

TEST(GlfwApi, info) {
  Engine e;
  e.registerApi<Glfw>();

  auto const& glfwApiInfo = e.apiList()[0]->apiInfo();
  ASSERT_EQ(glfwApiInfo.name, "GLFW"_s);
  ASSERT_EQ(glfwApiInfo.description, "Platform Independent API for window management and event handling"_s);
  ASSERT_EQ(glfwApiInfo.purpose, "mandatory=[surface, controller, keyboard, mouse, system], optional=[window]"_s);
  ASSERT_EQ(glfwApiInfo.vendor, "The GLFW Organization, domain - glfw.org, Licence Holder of GLFW - zlib/libpng licence"_s);
  ASSERT_EQ(glfwApiInfo.vendorId, Api::unknownVendorId);
  ASSERT_EQ(glfwApiInfo.sourceType, Api::SourceType::OpenSource);
  ASSERT_EQ(glfwApiInfo.version.variant, engine::variant::original);

  int maj;
  int min;
  int pat;
  glfwGetVersion(&maj, &min, &pat);
  auto u32 = [](int v){return static_cast <cds::uint32>(v);};

  ASSERT_EQ(glfwApiInfo.version.major, u32(maj));
  ASSERT_EQ(glfwApiInfo.version.minor, u32(min));
  ASSERT_EQ(glfwApiInfo.version.patch, u32(pat));
}

TEST(GlfwApi, components) {
  Engine e;
  e.registerApi<Glfw>();
  ASSERT_TRUE(e.apiList()[0]->components().empty());
}

TEST(GlfwApi, logging) {
  std::stringstream sb;
  auto e = makeUnique <Engine>();
  Logger& l = Logger::getLogger(Glfw::loggerName);
  l.outputs() = {sb};
  e->registerApi<Glfw>();
  e = nullptr;

  ASSERT_TRUE(contains(sb, "Initializing GLFW"));
  ASSERT_TRUE(contains(sb, "GLFW Initialized Successfully"));
  ASSERT_TRUE(contains(sb, "GLFW Shutting Down"));
}
