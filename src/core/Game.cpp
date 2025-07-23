#include "core/Game.hpp"
#include "engine/InputManager.hpp"
#include "engine/MeshCreator.hpp"
#include "engine/ObjectManager.hpp"
#include "engine/ResourceManager.hpp"
#include "glm/fwd.hpp"
#include <string>
#include <vector>

Game::Game(Window &game_wnd) : game_window(game_wnd) {};
Game::~Game() = default;

void Game::Start() {
  auto ambient = ResourceManager::LoadTexture(
      "container_albedo",
      "assets/textures/learnopengl-container/container2.png");
  auto specular = ResourceManager::LoadTexture(
      "container_specular",
      "assets/textures/learnopengl-container/container2_specular.png");

  auto material = ResourceManager::LoadMaterial(
      "container_material", "container_albedo", "container_specular", 32.0f);

  std::vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  for (int i = 0; i < cubePositions.size(); i++) {
    auto obj = std::make_shared<GameObject>();
    obj->SetMesh(ResourceManager::LoadMesh("Cube" + std::to_string(i),
                                           MeshCreator::CreateCube()));
    obj->SetMaterial(material);

    obj->transform.SetPosition(cubePositions[i]);
    obj->transform.SetRotation(glm::vec3(i * 10, 0, i * 10));

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

  default_shader->SetVec3("viewPos", camera.GetPosition());

  default_shader->SetVec3("directionalLight.ambient", glm::vec3(0.2f));
  default_shader->SetVec3("directionalLight.diffuse", glm::vec3(0.5f));
  default_shader->SetVec3("directionalLight.specular", glm::vec3(1.0f));
  default_shader->SetVec3("directionalLight.direction",
                          glm::vec3(-0.2f, -1.0f, -0.3f));

  default_shader->SetVec3("spotLight.position", camera.GetPosition());
  default_shader->SetVec3("spotLight.direction", camera.GetFront());
  default_shader->SetVec3("spotLight.ambient", glm::vec3(0.0f));
  default_shader->SetVec3("spotLight.diffuse", glm::vec3(1.0f));
  default_shader->SetVec3("spotLight.specular", glm::vec3(1.0f));
  default_shader->SetFloat("spotLight.constant", 1.0f);
  default_shader->SetFloat("spotLight.linear", 0.09f);
  default_shader->SetFloat("spotLight.quadratic", 0.032f);
  default_shader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
  default_shader->SetFloat("spotLight.outerCutOff",
                           glm::cos(glm::radians(17.5f)));

  std::vector<glm::vec3> pointLightsPositions = {
      glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
      glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f)};

  for (int i = 0; i < pointLightsPositions.size(); i++) {
    std::string lightName = "pointLights[" + std::to_string(i) + "]";

    default_shader->SetVec3(lightName + ".ambient", glm::vec3(0.2f));
    default_shader->SetVec3(lightName + ".diffuse", glm::vec3(0.5f));
    default_shader->SetVec3(lightName + ".specular", glm::vec3(1.0f));

    default_shader->SetVec3(lightName + ".position", pointLightsPositions[i]);
    default_shader->SetFloat(lightName + ".constant", 1.0f);
    default_shader->SetFloat(lightName + ".linear", 0.09f);
    default_shader->SetFloat(lightName + ".quadratic", 0.032f);
  }

  ObjectManager::Render(*default_shader);
}

void Game::Quit() { ResourceManager::Clear(); }
