#include "WindowManager.hpp"
#include "Error.hpp"

#include <stdexcept>

WindowManager::~WindowManager() {
  closeAll();
  glfwTerminate();
}

// Window array access (non-const)
Window &WindowManager::operator[](int i) { return *_windows[i]; }

// Window array access (const)
const Window &WindowManager::operator[](int i) const { return *_windows[i]; }

// Create a new window (using a default window name)
void WindowManager::create(WindowMode wMode, int width, int height) {
  static size_t index = 1;
  const std::string name = DEFAULT_WINDOW_NAME + std::to_string(index++);
  create(name, wMode, width, height);
}

// Creates a new window
void WindowManager::create(const std::string &name, WindowMode wMode, int width, int height) {
  _windows.emplace_back(std::move(std::unique_ptr<Window>(new Window(name, wMode, width, height))));
}

// Close a window at index
void WindowManager::close(size_t wIndex) { _windows.erase(_windows.begin() + wIndex); }

// Destroys all stored windows
void WindowManager::closeAll() { _windows.clear(); }

size_t WindowManager::numWindows() const { return _windows.size(); }

// Setup GFLW basic properties
void WindowManager::InitGLFW() {
  if (!glfwInit())
    throw std::runtime_error(buildErrMsg(ERROR::GLFW_INIT_FAILED, ERROR_TYPE::CRITICAL));

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
    throw std::runtime_error(buildErrMsg(ERROR::GLEW_INIT_FAILED, ERROR_TYPE::CRITICAL));

  // Allow modern extension features
  glewExperimental = GL_TRUE;
}