//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "core/Object.hpp"
#include "src/engine_v6/src/base/core/ResourceTracker.hpp"
#include <Engine.hpp>

#include <api/Api.hpp>
#include <api/component/RenderApiComponent.hpp>
#include "src/engine_v6/test/base/shared/TestApis.hpp"

namespace {
using engine::Engine;
using engine::Api;
using engine::ApiComponent;
using namespace cds;
using namespace cds::literals;
}

TEST(Api, info) {
  PApi api1(nullptr);
  ASSERT_EQ(api1.apiInfo().name, "PApi"_s);
  ASSERT_EQ(api1.apiInfo().description, "Proprietary Api"_s);
  ASSERT_EQ(api1.apiInfo().purpose, "none"_s);
  ASSERT_EQ(api1.apiInfo().vendor, "ProprietaryVendor"_s);
  ASSERT_EQ(api1.apiInfo().vendorId, 142);
  ASSERT_EQ(api1.apiInfo().sourceType, engine::Api::SourceType::Proprietary);
  ASSERT_EQ(api1.apiInfo().version.variant, engine::variant::original);
  ASSERT_EQ(api1.apiInfo().version.major, 1);
  ASSERT_EQ(api1.apiInfo().version.minor, 3);
  ASSERT_EQ(api1.apiInfo().version.patch, 0);

  OSApi api2(nullptr);
  ASSERT_EQ(api2.apiInfo().name, "OSApi"_s);
  ASSERT_EQ(api2.apiInfo().description, "Open Source Api"_s);
  ASSERT_EQ(api2.apiInfo().purpose, "none"_s);
  ASSERT_EQ(api2.apiInfo().vendor, "Unknown Foundation"_s);
  ASSERT_EQ(api2.apiInfo().vendorId, Api::unknownVendorId);
  ASSERT_EQ(api2.apiInfo().sourceType, engine::Api::SourceType::OpenSource);
  ASSERT_EQ(api2.apiInfo().version.variant, engine::variant::forked);
  ASSERT_EQ(api2.apiInfo().version.major, 2);
  ASSERT_EQ(api2.apiInfo().version.minor, 2);
  ASSERT_EQ(api2.apiInfo().version.patch, 5);

  TPApi api3(nullptr);
  ASSERT_EQ(api3.apiInfo().name, "TPApi"_s);
  ASSERT_EQ(api3.apiInfo().description, "Third Party Api"_s);
  ASSERT_EQ(api3.apiInfo().purpose, "none"_s);
  ASSERT_EQ(api3.apiInfo().vendor, "Unknown Vendor"_s);
  ASSERT_EQ(api3.apiInfo().vendorId, Api::unknownVendorId);
  ASSERT_EQ(api3.apiInfo().sourceType, engine::Api::SourceType::ThirdParty);
  ASSERT_EQ(api3.apiInfo().version.variant, engine::variant::original);
  ASSERT_EQ(api3.apiInfo().version.major, 1);
  ASSERT_EQ(api3.apiInfo().version.minor, 0);
  ASSERT_EQ(api3.apiInfo().version.patch, 16);
}

TEST(Api, engineGet) {
  Engine e1;
  Engine e2;

  PApi a1 (&e1);
  OSApi a2 (&e2);
  TPApi const a3 (nullptr);

  ASSERT_TRUE(a1.engine() == &e1);
  ASSERT_TRUE(a2.engine() == &e2);
  ASSERT_TRUE(a3.engine() == nullptr);
}

TEST(Api, components) {
  PApi api1(nullptr);
  OSApi api2(nullptr);

  ASSERT_EQ(api1.components().size(), 2);
  ASSERT_TRUE(api2.components().empty());

  ASSERT_TRUE(api1.components().any([](auto& e){return e->type() == ApiComponent::Type::Render;}));
  ASSERT_TRUE(api1.components().any([](auto& e){return e->type() == ApiComponent::Type::Keyboard;}));
  ASSERT_FALSE(api1.components().any([](auto& e){return e->type() == ApiComponent::Type::Mouse;}));

  auto const& capi1 = api1;
  ASSERT_TRUE(capi1.components().any([](auto& e){return e->type() == ApiComponent::Type::Render;}));
  ASSERT_TRUE(capi1.components().any([](auto& e){return e->type() == ApiComponent::Type::Keyboard;}));
  ASSERT_FALSE(capi1.components().any([](auto& e){return e->type() == ApiComponent::Type::Mouse;}));

  ASSERT_TRUE(api1.components().all([&api1](auto& e){return e->api() == &api1;}));
  ASSERT_TRUE(api1.components().all([&api1](auto const* e){return e->api() == &api1;}));

  ASSERT_TRUE(api2.components().all([&api2](auto& e){return e->api() == nullptr;}));
  ASSERT_TRUE(api2.components().all([&api2](auto const* e){return e->api() == nullptr;}));
}
