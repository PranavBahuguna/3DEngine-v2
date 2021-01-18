#pragma once

#include <string>

#include <GLFW/glfw3.h>

enum class WindowMode { WINDOWED, FULLSCREEN_WINDOWED, FULLSCREEN };

/**
 * The Window class stores a pointer to an internal GLFWwindow that can be accessed, as well as
 * provide a variety of initialization options and helper methods for setup. Window objects are
 * managed directly by the WindowManager class and thus cannot be created and destroyed
 * independently of WindowManager.
 */
class Window {
public:
  ~Window();

  GLFWwindow *getGLFWWindow();

  int getWidth() const;
  int getHeight() const;
  float getAspectRatio() const;

  friend class WindowManager;

private:
  Window(const std::string &name, WindowMode wMode, int width, int height, bool vsync);

  GLFWwindow *_glfwWindow;
  int _width;
  int _height;
};