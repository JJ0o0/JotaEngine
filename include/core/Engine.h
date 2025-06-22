#pragma once

#include "Window.h"
#include "Entity.h"
#include "Camera.h"
#include "graphics/Shader.h"
#include "ui/ImGuiManager.h"

class Engine {
private:
    Window window;
    Shader* shader;
    Shader* lightShader;

    std::vector<Entity*> entities;

    ImGuiManager* uiManager;
    
    float lastFrameTime = 0.0f;
    float deltaTime = 0.0f;
    
    static Camera* mainCamera;
    static void MouseCallbackBridge(GLFWwindow* window, double xpos, double ypos);

    void Render();
    void ImGuiRender();
    void ProcessInput();
    void UpdateDeltaTime();
public:
    Engine(int width, int height, const char* title);
    ~Engine();
    
    void Run();
};