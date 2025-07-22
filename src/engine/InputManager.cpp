#include "engine/InputManager.hpp"

bool InputManager::keys[1024] = {false};
bool InputManager::keys_pressed[1024] = {false};

bool InputManager::firstMouse = true;
double InputManager::lastX = 0.0;
double InputManager::lastY = 0.0;

bool InputManager::mouseLeftPressed = false;
float InputManager::mouseXOffset = 0.0f;
float InputManager::mouseYOffset = 0.0f;

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

void InputManager::MouseButtonCallback(GLFWwindow *window, int button,
                                       int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    mouseLeftPressed = (action == GLFW_PRESS);
  }
}

void InputManager::CursorPosCallback(GLFWwindow *window, double xpos,
                                     double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
    mouseXOffset = 0.0f;
    mouseYOffset = 0.0f;
    return;
  }

  mouseXOffset = (float)(xpos - lastX);
  mouseYOffset = (float)(lastY - ypos);

  lastX = xpos;
  lastY = ypos;
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

bool InputManager::IsMouseLeftPressed() { return mouseLeftPressed; }

float InputManager::GetMouseXOffset() { return mouseXOffset; }

float InputManager::GetMouseYOffset() { return mouseYOffset; }

void InputManager::ResetMouseOffsets() {
  mouseXOffset = 0.0f;
  mouseYOffset = 0.0f;
}

void InputManager::Update() { ResetMouseOffsets(); }
