#pragma once

#include <GL/glew.h>

#include "Window.hpp"

#include <memory>
#include <vector>

static constexpr const char *DEFAULT_WINDOW_NAME = "Window_";

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

  void create(WindowMode wMode = WindowMode::WINDOWED, int width = 800, int height = 600,
              bool vsync = false);
  void create(const std::string &name, WindowMode wMode = WindowMode::WINDOWED, int width = 800,
              int height = 600, bool vsync = false);
  void close(size_t wIndex);
  void closeAll();
  bool shouldClose(size_t wIndex = 0);
  void setContext(size_t wIndex = 0);
  void swapBuffers(size_t wIndex = 0);

  int getWidth(size_t wIndex = 0) const;
  int getHeight(size_t wIndex = 0) const;
  float getAspectRatio(size_t wIndex = 0) const;

  size_t numWindows() const;

private:
  inline static std::shared_ptr<WindowManager> INSTANCE;

  WindowManager() {}
  WindowManager(const WindowManager &) = delete;
  WindowManager &operator=(const WindowManager &) = delete;

  bool isValidWindowIndex(size_t index) const;

  static void InitGLFW();
  static void InitGLEW();

  std::vector<std::unique_ptr<Window>> m_windows;
};