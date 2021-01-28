#include "WindowManager.hpp"
#include "Windows.h"

#ifdef _DEBUG
static constexpr bool USE_FULLSCREEN = false;
#else
static constexpr bool USE_FULLSCREEN = true;
#endif

int main() {
  try {
    printf("Starting program...");

    // Create a single window
    WindowMode wMode = USE_FULLSCREEN ? WindowMode::FULLSCREEN : WindowMode::WINDOWED;
    WindowManager::Get().create(wMode);
    auto mainWindow = WindowManager::Get()[0].getGLFWWindow();

    // Remove cursor from screen
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(mainWindow)) {
      // Draw window
      glfwMakeContextCurrent(mainWindow);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(mainWindow);

      glfwPollEvents();
    }

  } catch (std::exception &e) {
    printf("A fatal error occurred!\n%s\n", e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}