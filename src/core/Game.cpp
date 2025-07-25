#include "core/Game.hpp"

#include "engine/InputManager.hpp"
#include "engine/Light.hpp"
#include "engine/ObjectManager.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/LightManager.hpp"

#include "glm/fwd.hpp"

#include <string>

Game::Game(Window &game_wnd) : game_window(game_wnd) {};
Game::~Game() = default;

void Game::Start() {
  StartLights();
  StartTextures();
  StartMaterials();
  StartObjects();
  StartShaders();
}

void Game::StartLights() {
  auto &lights = LightManager::Get();

  glm::vec3 directionalAmbient = glm::vec3(0.5f);
  glm::vec3 directionalDiffuse = glm::vec3(0.5f);
  glm::vec3 directionalSpecular = glm::vec3(1.0f);
  BaseLight base(directionalAmbient, directionalDiffuse, directionalSpecular);

  glm::vec3 directionalDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
  DirectionalLight directional(base, directionalDirection);

  PointLight point(base, glm::vec3(1.0f, 1.0f, 1.0f), 20);

  lights.CreateDirectionalLight(directional);
  lights.CreatePointLight(point);
}

void Game::StartTextures() {}

void Game::StartMaterials() {}

void Game::StartObjects() {
  auto obj = std::make_shared<GameObject>();
  auto model = ResourceManager::LoadModel(
      "backpack_model", "assets/models/backpack/backpack.obj");
  obj->SetModel(model);

  ObjectManager::Add(obj);
}

void Game::StartShaders() {
  default_shader = ResourceManager::LoadShader(
      "Default", "shaders/default.vert", "shaders/default.frag");
}

void Game::Update(float dt) {
  ObjectManager::Update(dt);

  if (game_window.IsCursorLocked()) {
    camera.KeyboardMovement(dt);
  }
}

void Game::Input() {
  if (InputManager::IsKeyPressedOnce(GLFW_KEY_ESCAPE)) {
    if (game_window.IsCursorLocked()) {
      game_window.LockCursor(false);
    } else {
      game_window.SetShouldClose(true);
    }
  }

  if (InputManager::IsMouseLeftPressed() and !game_window.IsCursorLocked()) {
    game_window.LockCursor(true);
  }

  if (game_window.IsCursorLocked()) {
    camera.MouseMovement();
  }

  InputManager::Update();
}

void Game::Render() {
  auto &lights = LightManager::Get();

  default_shader->Bind();

  camera.UpdateCameraVectors();

  default_shader->SetMatrix4("view", camera.GetViewMatrix());
  default_shader->SetMatrix4(
      "projection", camera.GetProjectionMatrix(game_window.GetAspectRatio()));

  default_shader->SetVec3("viewPos", camera.GetPosition());

  lights.SendToShader(*default_shader);
  ObjectManager::Render(*default_shader);
}

void Game::Quit() {
  LightManager::Get().Clear();
  ResourceManager::Clear();
}
