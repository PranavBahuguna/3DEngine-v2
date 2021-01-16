#pragma once

#include <memory>
#include <string>

// clang-format off
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// clang-format on

enum class WindowMode { WINDOWED, FULLSCREEN_WINDOWED, FULLSCREEN };

class WindowManager {
public:
  ~WindowManager();

  static std::shared_ptr<WindowManager> Get() {
    if (INSTANCE == nullptr) {
      // Initialise libraries and construct the window manager if accessing for the first time
      InitGLFW();
      InitGLEW();
      INSTANCE = std::shared_ptr<WindowManager>(new WindowManager());
    }
    return INSTANCE;
  }

  void createWindow(const std::string &name, WindowMode wMode, int width = 800, int height = 600,
                    bool vsync = false);

private:
  inline static std::shared_ptr<WindowManager> INSTANCE;

  WindowManager();
  WindowManager(const WindowManager &) = delete;
  WindowManager &operator=(const WindowManager &) = delete;

  static void InitGLFW();
  static void InitGLEW();

  GLFWwindow *m_window;
  int m_width;
  int m_height;
};