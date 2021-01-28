#pragma once

#include <stdarg.h>
#include <stdexcept>
#include <string>

enum class ERROR { GLFW_INIT_FAILED, GLFW_WINDOW_CREATE_FAILED, GLEW_INIT_FAILED };

enum class ERROR_TYPE { DEBUG, INFO, WARNING, CRITICAL };

#ifdef _DEBUG
static constexpr bool DEBUG_MODE = true;
#else
static constexpr bool DEBUG_MODE = false;
#endif

namespace detail {

// Sets an message header based on the error type raised
static void setMessageHeader(std::string &header, ERROR errCode, ERROR_TYPE errType) {
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

  header += std::to_string(static_cast<int>(errCode)) + ": ";
}

// Set the message body based on the error code
static void setMessageBody(std::string &body, ERROR errCode) {
  switch (errCode) {
  case ERROR::GLFW_INIT_FAILED:
    body = "GLFW initialization failed!";
    break;
  case ERROR::GLFW_WINDOW_CREATE_FAILED:
    body = "Failed to create window (%s).";
    break;
  case ERROR::GLEW_INIT_FAILED:
    body = "GLEW initialization failed!";
    break;
  default:
    body = "Unknown error.";
    break;
  }
}
} // namespace detail

// Construct a raised error with additional supplied arguments
static std::string buildErrMsg(ERROR errCode, ERROR_TYPE errType, ...) {
  // Do not print debug messages if we are not running in debug mode
  if (!DEBUG_MODE && errType == ERROR_TYPE::DEBUG)
    return "";

  std::string header, body;

  detail::setMessageHeader(header, errCode, errType);
  detail::setMessageBody(body, errCode);

  std::string errMsg = header + body + "\n";

  // Format the error message with all variadic arguments
  va_list args, args_copy;
  va_start(args, errType);
  va_copy(args_copy, args);

  int argsLen = vsnprintf(nullptr, 0, errMsg.c_str(), args_copy);
  if (argsLen < 0)
    throw std::runtime_error("Cannot encode supplied arguments.");

  std::string errMsgFormatted(size_t(argsLen) + 1, '\0');
  vsnprintf(errMsgFormatted.data(), errMsgFormatted.size(), errMsg.c_str(), args);
  errMsgFormatted.resize(argsLen);

  va_end(args);
  va_end(args_copy);

  return errMsgFormatted;
}