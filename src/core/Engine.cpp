#include "core/Engine.h"
#include "core/Camera.h"
#include "core/ResourceManager.h"
#include "core/Window.h"
#include "imgui.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

Camera* Engine::mainCamera = nullptr;

void Engine::MouseCallbackBridge(GLFWwindow* window, double xpos, double ypos) {
    if (mainCamera)
        mainCamera->GetMouseCallback(window, xpos, ypos);
}

Engine::Engine(int width, int height, const char* title) :
    window(width, height, title) {
    mainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    uiManager = new ImGuiManager(window.GetGLFWWindow());
    
    window.SetMouseCallback(MouseCallbackBridge);
    
    ResourceManager::LoadShader("default", "shaders/default.vert", "shaders/default.frag");
    ResourceManager::LoadShader("light", "shaders/light.vert", "shaders/light.frag");
    
    ResourceManager::LoadModel("crate", "assets/models/crate.glb");
    ResourceManager::LoadModel("rivet", "assets/models/rivet.obj");

    ResourceManager::LoadTexture("rivet_diffuse", "assets/images/rivet_diffuse.png");
    ResourceManager::LoadTexture("rivet_specular", "assets/images/rivet_specular.png");
    ResourceManager::LoadTexture("rivet_normal", "assets/images/rivet_normal.png");

    shader = ResourceManager::GetShader("default");
    lightShader = ResourceManager::GetShader("light");  

    Model* rivet = ResourceManager::GetModel("rivet");
    Model* light = ResourceManager::GetModel("crate");

    Material rivetMaterial;
    rivetMaterial.diffuse = ResourceManager::GetTexture("rivet_diffuse");
    rivetMaterial.specular = ResourceManager::GetTexture("rivet_specular");
    rivetMaterial.normal = ResourceManager::GetTexture("rivet_normal");
    rivetMaterial.shininess = 32.0f;

    Entity* rivetEntity = new Entity(rivet, shader);
    rivetEntity->SetMaterial(rivetMaterial);

    Entity* lightEntity = new Entity(light, lightShader);

    entities.push_back(rivetEntity);
    entities.push_back(lightEntity);
}

Engine::~Engine() {
    for (auto e : entities) {
        delete e;
    }
    delete mainCamera;

    entities.clear();

    ResourceManager::Cleanup();
}

void Engine::Run() {
    while (!window.ShouldClose()) {
        UpdateDeltaTime();
        ProcessInput();

        uiManager->BeginFrame();
        ImGuiRender();
        uiManager->EndFrame();
        Render();
        uiManager->Render();

        window.PollEvents();
        window.SwapBuffers();
    }
}

void Engine::Render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = mainCamera->GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), window.GetAspectRatio(), 0.1f, 100.0f);
    
    glm::vec3 centerPos = entities[0]->GetPosition();
    
    float radius = 2.0f;
    float speed = 1.0f;
    float time = glfwGetTime();

    float x = centerPos.x + radius * cos(speed * time);
    float y = centerPos.y + 1.0f;
    float z = centerPos.z + radius * sin(speed * time);

    lightShader->Use();
    lightShader->SetUniformMat4("view", view);
    lightShader->SetUniformMat4("projection", projection);

    entities[1]->SetPosition(glm::vec3(x, y, z));
    entities[1]->SetScale(glm::vec3(0.01f));
    entities[1]->Draw();
    
    shader->Use();
    shader->SetUniformMat4("view", view);
    shader->SetUniformMat4("projection", projection);
    shader->SetUniformVec3("viewPos", mainCamera->Position);
    shader->SetUniformVec3("lightPos", entities[1]->GetPosition());
    shader->SetUniformVec3("lightColor", glm::vec3(1.0f));

    entities[0]->SetScale(glm::vec3(0.1f));
    entities[0]->Draw();
}

void Engine::ImGuiRender() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_Always);
    ImGui::Begin("Configurações", nullptr,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoScrollbar
    );
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text("Propriedades da Camera");
    ImGui::Text("Posição: (%.2f, %.2f, %.2f)", 
        mainCamera->Position.x, 
        mainCamera->Position.y, 
        mainCamera->Position.z
    );
    ImGui::Text("Pitch: %.1f ", mainCamera->Pitch);
    ImGui::Text("Yaw: %.1f ", mainCamera->Yaw);
    ImGui::End();
}

void Engine::UpdateDeltaTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
}

void Engine::ProcessInput() {
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_ESCAPE))
        window.SetShouldClose(true);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_F1))
        window.SetMouseLock();

    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
        mainCamera->ProcessKeyboard(CameraDirection::FORWARD, deltaTime);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
        mainCamera->ProcessKeyboard(CameraDirection::BACKWARD, deltaTime);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
        mainCamera->ProcessKeyboard(CameraDirection::LEFT, deltaTime);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
        mainCamera->ProcessKeyboard(CameraDirection::RIGHT, deltaTime);

    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        mainCamera->ProcessKeyboard(CameraDirection::UP, deltaTime);
    if (glfwGetKey(window.GetGLFWWindow(), GLFW_KEY_C) == GLFW_PRESS)
        mainCamera->ProcessKeyboard(CameraDirection::DOWN, deltaTime);
}