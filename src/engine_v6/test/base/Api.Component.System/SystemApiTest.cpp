//
// Created by loghin on 5/9/23.
//

#include "Test.hpp"
#include "core/Object.hpp"
#include "src/engine_v6/src/base/core/ResourceTracker.hpp"
#include <Engine.hpp>
#include <api/component/SystemApiComponent.hpp>
#include "../../shared/TimeoutTest.hpp"

namespace {
using engine::Engine;
using engine::Api;
using engine::ApiComponent;
using engine::SystemApiComponent;
using namespace cds;
using namespace cds::literals;

class TestApi : public Api {
  class SysComp : public SystemApiComponent {
  public:
    explicit SysComp(TestApi* p) noexcept : SystemApiComponent(p) {
      shTh = new Runnable([this]{
        usleep(100);
        requestShutdown();
      });

      shTh->start();
    }

    ~SysComp() noexcept override {
      shTh->join();
    }

  private:
    cds::UniquePointer <cds::Thread> shTh;
  };
  static inline Info info {.name = "test"};
  SysComp c {this};
public:
  [[nodiscard]] const Info & apiInfo() const noexcept override {
    return info;
  }
  cds::Array<ApiComponent *> getComponentList() noexcept override {
    return {&c};
  }

  explicit TestApi(Engine* e) : Api(e) {}
};
}

TEST(SystemApiComponent, requestShutdown) {
  Engine e;
  e.registerApi<TestApi>();
  ASSERT_TRUE(timeoutTest([&e]{
    e.exec(0, nullptr);
  }, 100));
}

TEST(SystemApiComponent, type) {
  Engine e;
  e.registerApi<TestApi>();
  ASSERT_EQ(e.apiList()[0]->components()[0]->type(), ApiComponent::Type::System);
}

TEST(SystemApiComponent, info) {
  Engine e;
  e.registerApi<TestApi>();
  ASSERT_EQ(e.apiList()[0]->apiInfo().name, "test"_s);
}
