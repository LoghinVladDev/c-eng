//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#ifndef C_ENG_TESTAPIS_HPP
#define C_ENG_TESTAPIS_HPP

#include "src/engine_v6/src/base/api/Api.hpp"
#include "src/engine_v6/src/base/api/component/RenderApiComponent.hpp"
#include "src/engine_v6/src/base/api/component/KeyboardApiComponent.hpp"

namespace testing {
class PApi : public engine::Api {
  static inline Info info = {
      .name = "PApi",
      .description = "Proprietary Api",
      .purpose = "none",
      .vendor = "ProprietaryVendor",
      .vendorId = 142,
      .sourceType = engine::Api::SourceType::Proprietary,
      .version = {
          .variant = engine::variant::original,
          .major = 1,
          .minor = 3,
          .patch = 0
      }
  };

  class Dummy1Component : public engine::RenderApiComponent {public: explicit Dummy1Component(Api* api) : RenderApiComponent(api) {}};
  class Dummy2Component : public engine::KeyboardApiComponent {public: explicit Dummy2Component(Api* api) : KeyboardApiComponent(api) {}};
public:
  [[nodiscard]] const Info & apiInfo() const noexcept override {
    return info;
  }

  explicit PApi(engine::Engine* engine) noexcept : Api(engine) {}

  Dummy1Component d1 {this};
  Dummy2Component d2 {this};

  cds::Array<engine::ApiComponent *> getComponentList() noexcept override {
    return {&d1, &d2};
  }
};

class OSApi : public engine::Api {
  static inline Info info = {
      .name = "OSApi",
      .description = "Open Source Api",
      .purpose = "none",
      .vendor = "Unknown Foundation",
      .vendorId = unknownVendorId,
      .sourceType = engine::Api::SourceType::OpenSource,
      .version = {
          .variant = engine::variant::forked,
          .major = 2,
          .minor = 2,
          .patch = 5
      }
  };
public:
  [[nodiscard]] const Info & apiInfo() const noexcept override {
    return info;
  }
  explicit OSApi(engine::Engine* engine) noexcept : Api(engine) {}
};

class TPApi : public engine::Api {
  static inline Info info = {
      .name = "TPApi",
      .description = "Third Party Api",
      .purpose = "none",
      .vendor = "Unknown Vendor",
      .vendorId = unknownVendorId,
      .sourceType = engine::Api::SourceType::ThirdParty,
      .version = {
          .variant = engine::variant::original,
          .major = 1,
          .minor = 0,
          .patch = 16
      }
  };
public:
  [[nodiscard]] const Info & apiInfo() const noexcept override {
    return info;
  }
  explicit TPApi(engine::Engine* engine) noexcept : Api(engine) {}
};
} // namespace testing

#endif //C_ENG_TESTAPIS_HPP
