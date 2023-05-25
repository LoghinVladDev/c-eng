//
// Created by loghin on 30/04/23.
//

#include "Test.hpp"
#include "logging/Logger.hpp"
#include "../shared/LoggerShared.hpp"

TEST(LoggerEnabledFilter, individual) {
  auto [inf, wrn, err, dbg] = filterIndividual();

  ASSERT_TRUE(contains(inf, "Info"));
  ASSERT_TRUE(contains(inf, "test1"));
  ASSERT_FALSE(contains(inf, "Warning"));
  ASSERT_FALSE(contains(inf, "test2"));
  ASSERT_FALSE(contains(inf, "Error"));
  ASSERT_FALSE(contains(inf, "test3"));
  ASSERT_FALSE(contains(inf, "Debug"));
  ASSERT_FALSE(contains(inf, "test4"));

  ASSERT_FALSE(contains(wrn, "Info"));
  ASSERT_FALSE(contains(wrn, "test1"));
  ASSERT_TRUE(contains(wrn, "Warning"));
  ASSERT_TRUE(contains(wrn, "test2"));
  ASSERT_FALSE(contains(wrn, "Error"));
  ASSERT_FALSE(contains(wrn, "test3"));
  ASSERT_FALSE(contains(wrn, "Debug"));
  ASSERT_FALSE(contains(wrn, "test4"));

  ASSERT_FALSE(contains(err, "Info"));
  ASSERT_FALSE(contains(err, "test1"));
  ASSERT_FALSE(contains(err, "Warning"));
  ASSERT_FALSE(contains(err, "test2"));
  ASSERT_TRUE(contains(err, "Error"));
  ASSERT_TRUE(contains(err, "test3"));
  ASSERT_FALSE(contains(err, "Debug"));
  ASSERT_FALSE(contains(err, "test4"));

  ASSERT_FALSE(contains(dbg, "Info"));
  ASSERT_FALSE(contains(dbg, "test1"));
  ASSERT_FALSE(contains(dbg, "Warning"));
  ASSERT_FALSE(contains(dbg, "test2"));
  ASSERT_FALSE(contains(dbg, "Error"));
  ASSERT_FALSE(contains(dbg, "test3"));
  ASSERT_TRUE(contains(dbg, "Debug"));
  ASSERT_TRUE(contains(dbg, "test4"));
}

TEST(LoggerEnabledFilter, mixedOut) {
  auto [infWrn, wrnErr, errDbg] = filterMixedOut();

  ASSERT_TRUE(contains(infWrn, "Info"));
  ASSERT_TRUE(contains(infWrn, "test1"));
  ASSERT_TRUE(contains(infWrn, "Warning"));
  ASSERT_TRUE(contains(infWrn, "test2"));
  ASSERT_FALSE(contains(infWrn, "Error"));
  ASSERT_FALSE(contains(infWrn, "test3"));
  ASSERT_FALSE(contains(infWrn, "Debug"));
  ASSERT_FALSE(contains(infWrn, "test4"));

  ASSERT_FALSE(contains(wrnErr, "Info"));
  ASSERT_FALSE(contains(wrnErr, "test1"));
  ASSERT_TRUE(contains(wrnErr, "Warning"));
  ASSERT_TRUE(contains(wrnErr, "test2"));
  ASSERT_TRUE(contains(wrnErr, "Error"));
  ASSERT_TRUE(contains(wrnErr, "test3"));
  ASSERT_FALSE(contains(wrnErr, "Debug"));
  ASSERT_FALSE(contains(wrnErr, "test4"));

  ASSERT_FALSE(contains(errDbg, "Info"));
  ASSERT_FALSE(contains(errDbg, "test1"));
  ASSERT_FALSE(contains(errDbg, "Warning"));
  ASSERT_FALSE(contains(errDbg, "test2"));
  ASSERT_TRUE(contains(errDbg, "Error"));
  ASSERT_TRUE(contains(errDbg, "test3"));
  ASSERT_TRUE(contains(errDbg, "Debug"));
  ASSERT_TRUE(contains(errDbg, "test4"));
}
