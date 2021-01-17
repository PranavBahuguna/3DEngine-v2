#include "WindowManager.hpp"

int main() {
  auto windowManager = WindowManager::Get();
  windowManager->create("Win1", WindowMode::WINDOWED);
  windowManager->create("Win2", WindowMode::WINDOWED);

  while (!windowManager->shouldClose(0) && !windowManager->shouldClose(1)) {
    // Draw window 1
    windowManager->setContext(0);
    glClear(GL_COLOR_BUFFER_BIT);
    windowManager->swapBuffers(0);

    // Draw window 2
    windowManager->setContext(1);
    glClear(GL_COLOR_BUFFER_BIT);
    windowManager->swapBuffers(1);

    glfwPollEvents();
  }

  return EXIT_SUCCESS;
}