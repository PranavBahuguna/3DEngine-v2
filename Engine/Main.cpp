#include "WindowManager.hpp"

int main() {
  WindowManager::Get()->createWindow("Main", WindowMode::FULLSCREEN);
  
  while (true) {
  }

  return 0;
}