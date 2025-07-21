#include "engine/InputManager.hpp"

bool InputManager::keys[1024] = {false};
bool InputManager::keys_pressed[1024] = {false};

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  if (key >= 0 && key <= 1024) {
    if (action == GLFW_PRESS) {
      keys[key] = true;
      keys_pressed[key] = true;
    } else if (action == GLFW_RELEASE) {
      keys[key] = false;
    }
  }
}

bool InputManager::IsKeyPressed(int key) {
  if (key >= 0 && key <= 1024) {
    return keys[key];
  }

  return false;
}

bool InputManager::IsKeyPressedOnce(int key) {
  if (key >= 0 && key <= 1024 && keys_pressed[key]) {
    keys_pressed[key] = false;

    return true;
  }

  return false;
}

void InputManager::Update() {}
