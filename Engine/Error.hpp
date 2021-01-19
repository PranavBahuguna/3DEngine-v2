#pragma once

#include <cstdint>
#include <stdarg.h>
#include <stdexcept>
#include <string>

namespace Error {

typedef uint32_t ERROR;

enum class ERROR_TYPE { DEBUG, INFO, WARNING, CRITICAL };

// clang-format off
static constexpr ERROR ERROR_GLFW_INIT_FAILED                 = 0;
static constexpr ERROR ERROR_GLFW_WINDOW_CREATE_FAILED        = 1;
static constexpr ERROR ERROR_GLEW_INIT_FAILED                 = 2;
// clang-format on

#ifdef _DEBUG
static constexpr bool DEBUG_MODE = true;
#else
static constexpr bool DEBUG_MODE = false;
#endif

// Print and handle a raised error with additional supplied arguments
static void raiseError(ERROR errCode, ERROR_TYPE errType, ...) {
  // Do not print debug messages if we are not running in debug mode
  if (!DEBUG_MODE && errType == ERROR_TYPE::DEBUG)
    return;

  std::string header;
  std::string body;

  // Set the message header based on the error type raised
  switch (errType) {
  case ERROR_TYPE::DEBUG:
    header = "[DEBUG] ";
    break;
  case ERROR_TYPE::INFO:
    header = "[INFO] ";
    break;
  case ERROR_TYPE::WARNING:
    header = "[WARNING] ";
    break;
  case ERROR_TYPE::CRITICAL:
  default:
    header = "[ERROR] ";
    break;
  }

  header += std::to_string(errCode) + ": ";

  // Set the message body based on the error code and any additional arguments
  switch (errCode) {
  case ERROR_GLFW_INIT_FAILED:
    body = "GLFW initialization failed!";
    break;
  case ERROR_GLFW_WINDOW_CREATE_FAILED:
    body = "Failed to create window (%s).";
    break;
  case ERROR_GLEW_INIT_FAILED:
    body = "GLEW initialization failed!";
    break;
  default:
    body = "Unknown error.";
    break;
  }

  std::string errMsg = header + body + "\n";

  // Add all variadic arguments to be printed
  va_list args;
  va_start(args, errType);
  vprintf(errMsg.c_str(), args);
  va_end(args);

  // Throw an exception if we have a critical error
  if (errType == ERROR_TYPE::CRITICAL)
    throw std::runtime_error("A critical error was thrown!");
}
} // namespace Error