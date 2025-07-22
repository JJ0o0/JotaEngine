#pragma once

#include <GLFW/glfw3.h>

class InputManager {
public:
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static void MouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);

  static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);

  static bool IsKeyPressed(int key);
  static bool IsKeyPressedOnce(int key);

  static bool IsMouseLeftPressed();

  static float GetMouseXOffset();
  static float GetMouseYOffset();

  static void ResetMouseOffsets();

  static void Update();

private:
  static bool keys[1024];
  static bool keys_pressed[1024];

  static bool firstMouse;
  static double lastX;
  static double lastY;

  static bool mouseLeftPressed;
  static float mouseXOffset;
  static float mouseYOffset;
};
