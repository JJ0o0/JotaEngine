#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>

class ImGuiManager {
private:
    GLFWwindow* m_window;
public:
    ImGuiManager(GLFWwindow* window);
    ~ImGuiManager();

    void BeginFrame();
    void EndFrame();

    void Render();
};