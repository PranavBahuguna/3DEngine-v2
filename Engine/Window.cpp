#include "Window.hpp"
#include "Error.hpp"

#include <stdexcept>

Window::Window(const std::string &name, WindowMode wMode, int width, int height) : _name(name) {

  // Set window dimensions from screen if fullscreen is enabled
  GLFWmonitor *monitor = nullptr;
  if (wMode == WindowMode::FULLSCREEN || wMode == WindowMode::FULLSCREEN_WINDOWED) {
    auto primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    width = mode->width;
    height = mode->height;

    // Use the primary monitor if we want non-windowed fullscreen
    if (wMode == WindowMode::FULLSCREEN)
      monitor = primaryMonitor;
  }

  // Try creating the window
  _glfwWindow = glfwCreateWindow(width, height, name.c_str(), monitor, NULL);
  if (_glfwWindow == nullptr)
    throw std::runtime_error(
        buildErrMsg(ERROR::GLFW_WINDOW_CREATE_FAILED, ERROR_TYPE::CRITICAL, name.c_str()));

  // Setup keyboard and mouse handlers
  // ...
}

Window::~Window() { glfwDestroyWindow(_glfwWindow); }

GLFWwindow *Window::getGLFWWindow() { return _glfwWindow; }

std::string Window::getName() const { return _name; }