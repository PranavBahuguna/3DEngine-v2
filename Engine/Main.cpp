#include "WindowManager.hpp"
#include "Windows.h"

#ifdef _DEBUG
#define WINDOW_MODE WindowMode::WINDOWED
#else
#define WINDOW_MODE WindowMode::FULLSCREEN
#endif

int main() {
  try {
    WindowManager::Get().create(WINDOW_MODE);
    WindowManager::Get().create(WINDOW_MODE);
    auto mainWindow = WindowManager::Get()[0].getGLFWWindow();
    auto mainWindow2 = WindowManager::Get()[1].getGLFWWindow();

    while (!glfwWindowShouldClose(mainWindow) || !glfwWindowShouldClose(mainWindow2)) {
      // Draw window
      glfwMakeContextCurrent(mainWindow);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(mainWindow);

      // Draw window
      glfwMakeContextCurrent(mainWindow2);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(mainWindow2);

      glfwPollEvents();
    }

  } catch (std::exception &e) {
    printf(e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}