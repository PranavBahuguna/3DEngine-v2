#include "WindowManager.hpp"

#include <stdexcept>

WindowManager::~WindowManager() {
  closeAll();
  glfwTerminate();
}

// Create a new window (using a default window name)
void WindowManager::create(WindowMode wMode, int width, int height, bool vsync) {
  static size_t index = 1;
  const std::string name = DEFAULT_WINDOW_NAME + std::to_string(index++);
  create(DEFAULT_WINDOW_NAME, wMode, width, height, vsync);
}

// Creates a new window
void WindowManager::create(const std::string &name, WindowMode wMode, int width, int height,
                           bool vsync) {
  m_windows.emplace_back(
      std::move(std::unique_ptr<Window>(new Window(name, wMode, width, height, vsync))));
}

// Close a window at index
void WindowManager::close(size_t wIndex) {
  if (isValidWindowIndex(wIndex))
    m_windows.erase(m_windows.begin() + wIndex);
}

// Destroys all stored windows
void WindowManager::closeAll() { m_windows.clear(); }

bool WindowManager::shouldClose(size_t wIndex) {
  return isValidWindowIndex(wIndex) ? m_windows[wIndex]->shouldClose() : false;
}

void WindowManager::setContext(size_t wIndex) {
  if (isValidWindowIndex(wIndex))
    m_windows[wIndex]->setContext();
}

void WindowManager::swapBuffers(size_t wIndex) {
  if (isValidWindowIndex(wIndex))
    m_windows[wIndex]->swapBuffers();
}

int WindowManager::getWidth(size_t wIndex) const {
  return isValidWindowIndex(wIndex) ? m_windows[wIndex]->getWidth() : 0;
}

int WindowManager::getHeight(size_t wIndex) const {
  return isValidWindowIndex(wIndex) ? m_windows[wIndex]->getHeight() : 0;
}

float WindowManager::getAspectRatio(size_t wIndex) const {
  return isValidWindowIndex(wIndex) ? m_windows[wIndex]->getAspectRatio() : 0.0f;
}

size_t WindowManager::numWindows() const { return m_windows.size(); }

// Check if the window index lies in range
bool WindowManager::isValidWindowIndex(size_t wIndex) const {
  bool isValid = wIndex < m_windows.size();
  if (!isValid)
    printf("Error, index is out of range");

  return isValid;
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