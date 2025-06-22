#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
    int width, height;
    const char* title;

    bool locked = false;

    GLFWwindow* window;
public:
    Window(int w, int h, const char* t);
    ~Window();

    void SetShouldClose(bool value);
    void SetMouseLock();
    void SetMouseCallback(void (*func)(GLFWwindow*, double, double));

    bool ShouldClose() const;

    void PollEvents() const;
    void SwapBuffers() const;

    GLFWwindow* GetGLFWWindow() const;

    float GetAspectRatio() const;
};