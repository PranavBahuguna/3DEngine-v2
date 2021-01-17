#include "Window.hpp"

#include <stdexcept>

Window::Window(const std::string &name, WindowMode wMode, int width, int height, bool vsync)
    : m_width(width), m_height(height) {

  // Set window dimensions from screen if fullscreen is enabled
  GLFWmonitor *monitor = nullptr;
  if (wMode == WindowMode::FULLSCREEN || wMode == WindowMode::FULLSCREEN_WINDOWED) {
    auto primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
    m_width = mode->width;
    m_height = mode->height;

    // Use the primary monitor if we want non-windowed fullscreen
    if (wMode == WindowMode::FULLSCREEN)
      monitor = primaryMonitor;
  }

  // Try creating the window
  m_window = glfwCreateWindow(m_width, m_height, name.c_str(), monitor, NULL);
  if (m_window == nullptr)
    throw std::runtime_error("An error occurred while creating window.");

  // Setup keyboard and mouse handlers
  // ...

  // Remove cursor from screen
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window() { glfwDestroyWindow(m_window); }

void Window::close() { glfwSetWindowShouldClose(m_window, true); }

bool Window::shouldClose() { return glfwWindowShouldClose(m_window); }

void Window::setContext() { glfwMakeContextCurrent(m_window); }

void Window::swapBuffers() { glfwSwapBuffers(m_window); }

int Window::getWidth() const { return m_width; }

int Window::getHeight() const { return m_height; }

float Window::getAspectRatio() const { return (float)m_width / (float)m_height; }