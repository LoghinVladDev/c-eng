//
// Created by Vlad-Andrei Loghin on 15.06.23.
//

#ifndef C_ENG_TIMEOUTTEST_HPP
#define C_ENG_TIMEOUTTEST_HPP
#include <CDS/threading/Thread>

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

#endif //C_ENG_TIMEOUTTEST_HPP
