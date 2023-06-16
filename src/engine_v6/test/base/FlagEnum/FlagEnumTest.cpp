//
// Created by Vlad-Andrei Loghin on 16.06.23.
//

#include "lang/FlagEnum.hpp"
#include "../../Test.hpp"

namespace {
using namespace cds;
using namespace engine;
using namespace engine::meta;

enum class TestFlag : cds::uint8 {
  First = 0x01,
  Second = 0x02,
  Third = 0x04,
  Fourth = 0x08
};
using Flags = std::underlying_type_t<TestFlag>;
using enum TestFlag;
}

template <>
struct engine::meta::FlagEnum <TestFlag> : cds::meta::TrueType {
  using FlagsType = Flags;
};


TEST(FlagEnumTest, bwOr) {
  TestFlag a = Second;
  TestFlag b = Fourth;

  auto c = a | b;
  auto d = c | First;
  auto e = Third | d;

  ASSERT_EQ(c, 0xa);
  ASSERT_EQ(d, 0xb);
  ASSERT_EQ(e, 0xf);
}


TEST(FlagEnumTest, bwAnd) {
  TestFlag a = Second;
  TestFlag b = Fourth;

  auto c = a & b;
  auto d = c & First;
  auto e = Third & d;

  ASSERT_EQ(c, 0x0);
  ASSERT_EQ(d, 0x0);
  ASSERT_EQ(e, 0x0);
}


TEST(FlagEnumTest, bwXor) {
  TestFlag a = Second;
  TestFlag b = Fourth;

  auto c = a ^ b;
  auto d = c ^ First;
  auto e = Third ^ d;

  ASSERT_EQ(c, 0xa);
  ASSERT_EQ(d, 0xb);
  ASSERT_EQ(e, 0xf);
  ASSERT_EQ(e ^ Second, 0xd);
}

TEST(FlagEnumTest, bwNot) {
  TestFlag a = Fourth;
  ASSERT_EQ(~a, First | Second | Third | 0xf0);
}

TEST(FlagEnumTest, accum) {
  Flags f = 0;

  f|=Second;
  f|=Third;

  ASSERT_EQ(f, 0x6);

  f&= Third;

  ASSERT_EQ(f, 0x4);

  f^= Third;
  f^= Fourth;

  ASSERT_EQ(f, 0x8);
}

TEST(FlagEnumTest, comp) {
  bool b;
  b = (Second == 0x2);
  ASSERT_TRUE(b);
  b = (0x2 == Second);
  ASSERT_TRUE(b);

  b = (Second != 0x1);
  ASSERT_TRUE(b);
  b = (0x1 != Second);
  ASSERT_TRUE(b);

  b = (Second > First);
  ASSERT_TRUE(b);
  b = (Second > 0x1);
  ASSERT_TRUE(b);
  b = (0x4 > Second);
  ASSERT_TRUE(b);

  b = (Second < Third);
  ASSERT_TRUE(b);
  b = (Second < 0x4);
  ASSERT_TRUE(b);
  b = (0x1 < Second);
  ASSERT_TRUE(b);

  b = (Second >= First);
  ASSERT_TRUE(b);
  b = (Second >= 0x1);
  ASSERT_TRUE(b);
  b = (Second >= 0x2);
  ASSERT_TRUE(b);
  b = (0x4 > Second);
  ASSERT_TRUE(b);
  b = (0x2 >= Second);
  ASSERT_TRUE(b);

  b = (Second <= Third);
  ASSERT_TRUE(b);
  b = (Second <= 0x4);
  ASSERT_TRUE(b);
  b = (Second <= 0x2);
  ASSERT_TRUE(b);
  b = (0x1 <= Second);
  ASSERT_TRUE(b);
  b = (0x2 <= Second);
  ASSERT_TRUE(b);
}
