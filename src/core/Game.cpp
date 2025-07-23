#include "core/Game.hpp"
#include "engine/InputManager.hpp"
#include "engine/MeshCreator.hpp"
#include "engine/ObjectManager.hpp"
#include "engine/ResourceManager.hpp"

Game::Game(Window &game_wnd) : game_window(game_wnd) {};
Game::~Game() = default;

void Game::Start() {
  auto obj = std::make_shared<GameObject>("Cube");
  obj->SetMesh(ResourceManager::LoadMesh("Cube", MeshCreator::CreateCube()));

  auto ambient = ResourceManager::LoadTexture(
      "container_albedo",
      "assets/textures/learnopengl-container/container2.png");
  auto specular = ResourceManager::LoadTexture(
      "container_specular",
      "assets/textures/learnopengl-container/container2_specular.png");

  auto material = ResourceManager::LoadMaterial(
      "container_material", "container_albedo", "container_specular", 32.0f);

  obj->SetMaterial(material);

  ObjectManager::Add(obj);

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

  default_shader->SetVec3("viewPos", camera.GetPosition());

  // o cara que fez as docs do learnopengl tava bricando com isso...
  // então eu também quero brincar.
  glm::vec3 lightColor;
  lightColor.x = sin(glfwGetTime() * 2.0f);
  lightColor.y = sin(glfwGetTime() * 0.7f);
  lightColor.z = sin(glfwGetTime() * 1.3f);

  glm::vec3 diffuse = lightColor * glm::vec3(0.5f);
  glm::vec3 ambient = lightColor * glm::vec3(0.2f);

  default_shader->SetVec3("light.ambient", ambient);
  default_shader->SetVec3("light.diffuse", diffuse);
  default_shader->SetVec3("light.specular", glm::vec3(1.0f));
  default_shader->SetVec3("light.position", glm::vec3(1.2f, 1.0f, 2.0f));

  ObjectManager::Render(*default_shader);
}

void Game::Quit() { ResourceManager::Clear(); }
