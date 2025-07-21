#pragma once

#include <GLFW/glfw3.h>

class InputManager {
public:
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);

  static bool IsKeyPressed(int key);
  static bool IsKeyPressedOnce(int key);

  static void Update();

private:
  static bool keys[1024];
  static bool keys_pressed[1024];
};
