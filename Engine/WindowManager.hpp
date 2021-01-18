#pragma once

#include <GL/glew.h>

#include "Window.hpp"

#include <memory>
#include <vector>

static constexpr const char *DEFAULT_WINDOW_NAME = "Window_";

/**
 * The WindowManager class is a singleton that provides facilities for creating, storing and
 * destroying Window instances. Additionally on startup, it will also begin initialization of the
 * GLFW and GLEW libraries before any window can be created.
 *
 * The array subscript operator for this class is overloaded to provide easy access to all stored
 * window objects. For example, to find the height of the first window stored:
 *
 *     int winHeight = WindowManager::Get()[0].getHeight();
 */
class WindowManager {
public:
  ~WindowManager();

  static WindowManager &Get() {
    if (INSTANCE == nullptr) {
      // Initialise libraries and construct the window manager if accessing for the first time
      InitGLFW();
      InitGLEW();
      INSTANCE = std::shared_ptr<WindowManager>(new WindowManager());
    }
    return *INSTANCE;
  }

  // Overloaded array subscript operator for access to held window objects
  Window &operator[](int i);
  const Window &operator[](int i) const;

  void create(WindowMode wMode = WindowMode::WINDOWED, int width = 2000, int height = 1500,
              bool vsync = false);
  void create(const std::string &name, WindowMode wMode = WindowMode::WINDOWED, int width = 2000,
              int height = 1500, bool vsync = false);
  void close(size_t wIndex = 0);
  void closeAll();

  size_t numWindows() const;

private:
  inline static std::shared_ptr<WindowManager> INSTANCE;

  WindowManager() {}
  WindowManager(const WindowManager &) = delete;
  WindowManager &operator=(const WindowManager &) = delete;

  static void InitGLFW();
  static void InitGLEW();

  std::vector<std::shared_ptr<Window>> _windows;
};