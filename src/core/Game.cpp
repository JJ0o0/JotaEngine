#include "core/Game.hpp"
#include "engine/InputManager.hpp"
#include "engine/MeshCreator.hpp"
#include "engine/ObjectManager.hpp"
#include "engine/ResourceManager.hpp"

Game::Game(Window &game_wnd) : game_window(game_wnd) {};
Game::~Game() = default;

void Game::Start() {
  std::vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  for (int i = 0; i < cubePositions.size(); i++) {
    auto obj = std::make_shared<GameObject>("Cube" + std::to_string(i));
    obj->SetMesh(ResourceManager::LoadMesh("Cube", MeshCreator::CreateCube()));

    if (i % 2) {
      obj->SetTexture(ResourceManager::LoadTexture(
          "Brick", "assets/textures/bricks/brick_albedo.jpg"));
    } else {
      obj->SetTexture(ResourceManager::LoadTexture(
          "Wood", "assets/textures/wood/wood_albedo.jpg"));
    }

    obj->transform.SetPosition(cubePositions.at(i));

    float angle = 20.0f * i;
    obj->transform.SetRotation(glm::vec3(angle, angle * 0.3f, angle * 0.5f));

    ObjectManager::Add(obj);
  }

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
  default_shader->Bind();

  camera.UpdateCameraVectors();

  default_shader->SetMatrix4("view", camera.GetViewMatrix());
  default_shader->SetMatrix4(
      "projection", camera.GetProjectionMatrix(game_window.GetAspectRatio()));

  ObjectManager::Render(*default_shader);
}

void Game::Quit() { ResourceManager::Clear(); }
