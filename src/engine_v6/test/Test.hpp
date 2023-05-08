//
// Created by loghin on 30/04/23.
//

#ifndef C_ENG_TEST_HPP
#define C_ENG_TEST_HPP

#include <CDS/memory/UniquePointer>
#include <CDS/Array>
#include <CDS/String>
#include <source_location>

#define TEST(instance, name) \
namespace testing {          \
class TI ## instance ## name : public Test {                        \
public:                                                             \
  TI ## instance ## name () noexcept :                            \
          Test(#instance, #name) {                                \
                                                                  \
      unit->emplaceBack(this);                                    \
  }                                                               \
                                                                  \
  auto run() const noexcept(false) -> void override;              \
};                                                                  \
                                                                    \
TI ## instance ## name const instance ## TI ## instance ## name;    \
}                                                                       \
                                                                        \
                                                                        \
auto testing::TI ## instance ## name :: run() const noexcept(false) -> void

#define ASSERT_TRUE(expression) \
  (expression) ? _noassert() : _assert("Expected " #expression " true, got false instead")
#define ASSERT_FALSE(expression) \
  (expression) ? _assert("Expected " #expression " false, got true instead") : _noassert()
#define ASSERT_EQ(left, right) \
  ((left)==(right)) ? _noassert() : _assert("Expected " #left " == " #right)
#define ASSERT_NE(left, right) \
  ((left)!=(right)) ? _noassert() : _assert("Expected " #left " != " #right)
#define ASSERT_GE(left, right) \
  ((left)>=(right)) ? _noassert() : _assert("Expected " #left " >= " #right)
#define ASSERT_LE(left, right) \
  ((left)<=(right)) ? _noassert() : _assert("Expected " #left " <= " #right)
#define ASSERT_GT(left, right) \
  ((left)>(right)) ? _noassert() : _assert("Expected " #left " > " #right)
#define ASSERT_LT(left, right) \
  ((left)<(right)) ? _noassert() : _assert("Expected " #left " < " #right)

namespace testing {
class TestAssert : public cds::Exception {
public:
  TestAssert(cds::String const& reason, cds::String const& tName, std::source_location const& location) noexcept:
      Exception (
          cds::String() + location.file_name() + ":" + location.line() + " Assertion failed in test " +
          tName + ": " + reason
      ) {
  }
};

class Test {
public:
  Test(cds::StringView instance, cds::StringView name) noexcept:
      _instance(std::move(instance)), _name(std::move(name)) {

  }

  virtual ~Test() noexcept = default;
  virtual auto run() const noexcept(false) -> void = 0;
  [[nodiscard]] auto start() const noexcept -> bool;

protected:
  [[noreturn]] auto _assert(cds::String const& reason, std::source_location const& location = std::source_location::current()) const noexcept(false) -> void {
    throw TestAssert(reason, _instance + "-" + _name, location);
  }

  auto _noassert() const noexcept -> void {
    // intentionally empty
  }

private:
  cds::StringView _instance;
  cds::StringView _name;
};

auto Test::start() const noexcept -> bool {
  bool status = true;
  try {
    run();
    std::cout << "\033[1;32mTest " << _instance << " " << _name << " ran successfully\n";
  } catch (TestAssert const & assert) {
    std::cout << "\033[1;31mTest " << _instance << " " << _name << " failed\n";
    std::cout << "  " << assert.message() << '\n';
    status = false;
  }
  std::cout << "\033[1;0m";
  return status;
}

auto const unit = cds::makeUnique <cds::Array <Test*>> ();
}

auto main () noexcept -> int {
  using testing::unit;
  for (auto& pTest: *unit) {
    auto status = pTest->start();
    if (! status) {
      return 1;
    }
  }

  return 0;
}

#endif //C_ENG_TEST_HPP
