#include "WindowManager.hpp"

#include <stdexcept>

WindowManager::WindowManager() : m_window(nullptr), m_width(0), m_height(0) {}

WindowManager::~WindowManager() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

// Creates a new window
void WindowManager::createWindow(const std::string &name, WindowMode wMode, int width, int height,
                                 bool vsync) {

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
  } else {
    // Set window dimensions from supplied arguments
    m_width = width;
    m_height = height;
  }

  // Try creating the window
  m_window = glfwCreateWindow(m_width, m_height, name.c_str(), monitor, NULL);
  if (m_window == nullptr)
    throw std::runtime_error("An error occurred while creating window.");

  // Set context for GLEW to use
  glfwMakeContextCurrent(m_window);

  // Setup viewport size
  glViewport(0, 0, m_width, m_height);

  // Setup keyboard and mouse handlers
  // ...

  // Remove cursor from screen
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

// Setup GFLW basic properties
void WindowManager::InitGLFW() {
  if (!glfwInit())
    return;

  // OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // Core profile - no backwards compatibility
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Allow forwards compatibility
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

// Setup GLEW basic properties
void WindowManager::InitGLEW() {
  if (!glewInit())
    return;

  // Allow modern extension features
  glewExperimental = GL_TRUE;
}