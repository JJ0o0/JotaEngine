#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Window {
public:
  Window(const int width, const int height, const char *title);
  ~Window();

  bool Init();
  void Terminate();

  float GetDeltaTime();

  void SwapBuffers() const;
  void PollEvents() const;

  void LockCursor(bool enable);
  bool IsCursorLocked() const;

  void SetShouldClose(bool value);
  bool ShouldClose() const;

  float GetAspectRatio() const;

  std::string GetSystemName();

  GLFWwindow *GetNative() const;

private:
  GLFWwindow *window;

  const int width;
  const int height;
  const char *title;

  float lastFrameTime;
};
