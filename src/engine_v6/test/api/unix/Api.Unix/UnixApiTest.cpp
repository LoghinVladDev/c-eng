//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "src/engine_v6/src/api/unix/Unix.hpp"
#include "src/engine_v6/src/base/Engine.hpp"

namespace  {
using engine::Unix;
using engine::Engine;
using engine::Api;
using namespace cds;
using namespace cds::literals;
}

TEST(UnixApi, info) {
  Engine e;
  e.registerApi<Unix>();

  auto const& unixApiInfo = e.apiList()[0]->apiInfo();
  ASSERT_EQ(unixApiInfo.name, "Unix System API"_s);
  ASSERT_EQ(unixApiInfo.description, "System Interaction with Unix Based OS"_s);
  ASSERT_EQ(unixApiInfo.purpose, "mandatory=[system], optional=[]"_s);
  ASSERT_EQ(unixApiInfo.vendor, "TBA"_s);
  ASSERT_EQ(unixApiInfo.vendorId, Api::unknownVendorId);
  ASSERT_EQ(unixApiInfo.sourceType, Api::SourceType::OpenSource);
  ASSERT_EQ(unixApiInfo.version.variant, engine::variant::original);
  ASSERT_EQ(unixApiInfo.version.major, engine::version::unspecified);
  ASSERT_EQ(unixApiInfo.version.minor, engine::version::unspecified);
  ASSERT_EQ(unixApiInfo.version.patch, engine::version::unspecified);
}

TEST(UnixApi, components) {
  Engine e;
  e.registerApi<Unix>();

  ASSERT_EQ(e.apiList()[0]->components().size(), 1);
  ASSERT_EQ(e.apiList()[0]->components()[0]->type(), engine::ApiComponent::Type::System);
}
