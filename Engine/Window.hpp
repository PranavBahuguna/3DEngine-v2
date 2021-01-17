#pragma once

#include <string>

#include <GLFW/glfw3.h>

enum class WindowMode { WINDOWED, FULLSCREEN_WINDOWED, FULLSCREEN };

class Window {
public:
  ~Window();

  void close();
  bool shouldClose();
  void setContext();
  void swapBuffers();

  int getWidth() const;
  int getHeight() const;
  float getAspectRatio() const;

  friend class WindowManager;

private:
  // Private constructor - can only be created by WindowManager
  Window(const std::string &name, WindowMode wMode, int width, int height, bool vsync);

  GLFWwindow *m_window;
  int m_width;
  int m_height;
};