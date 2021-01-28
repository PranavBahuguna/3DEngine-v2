#include "WindowManager.hpp"
#include <Windows.h>

#define BOOST_TEST_MODULE WindowManagerTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Test_CreatingAndDeletingWindowsReturnsExpectedAmount) {
  auto &windowManager = WindowManager::Get();

  // Creating windows
  windowManager.create("w1");
  windowManager.create("w2");
  windowManager.create("w3");
  windowManager.create("w4");

  BOOST_CHECK_EQUAL(windowManager.numWindows(), 4);
  BOOST_CHECK_EQUAL(windowManager[0].getName(), "w1");
  BOOST_CHECK_EQUAL(windowManager[1].getName(), "w2");
  BOOST_CHECK_EQUAL(windowManager[2].getName(), "w3");
  BOOST_CHECK_EQUAL(windowManager[3].getName(), "w4");

  // Closing windows
  windowManager.close(1);
  windowManager.close(2);

  BOOST_CHECK_EQUAL(windowManager.numWindows(), 2);
  BOOST_CHECK_EQUAL(windowManager[0].getName(), "w1");
  BOOST_CHECK_EQUAL(windowManager[1].getName(), "w3");

  windowManager.closeAll();

  BOOST_CHECK_EQUAL(windowManager.numWindows(), 0);
}