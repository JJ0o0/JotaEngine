#include "core/Game.hpp"

#include "engine/InputManager.hpp"
#include "engine/Light.hpp"
#include "engine/MeshCreator.hpp"
#include "engine/ObjectManager.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/LightManager.hpp"

#include "glm/fwd.hpp"

#include <string>
#include <vector>

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

  glm::vec3 pointAmbient = glm::vec3(0.5f);
  glm::vec3 pointDiffuse = glm::vec3(0.75f);
  glm::vec3 pointSpecular = glm::vec3(1.0f);
  BaseLight pointBase(pointAmbient, pointDiffuse, pointSpecular);

  std::vector<glm::vec3> pointPositions = {
      glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
      glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f)};

  float pointRange = 20.0f;
  for (const auto &pos : pointPositions) {
    PointLight light(pointBase, pos, pointRange);
    lights.CreatePointLight(light);
  }

  lights.CreateDirectionalLight(directional);
}

void Game::StartTextures() {
  ResourceManager::LoadTexture(
      "container_albedo",
      "assets/textures/learnopengl-container/container2.png");

  ResourceManager::LoadTexture(
      "container_specular",
      "assets/textures/learnopengl-container/container2_specular.png");
}

void Game::StartMaterials() {
  ResourceManager::LoadMaterial("container_material", "container_albedo",
                                "container_specular", 32.0f);
}

void Game::StartObjects() {
  std::vector<glm::vec3> cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  auto mat = ResourceManager::GetMaterial("container_material");
  for (size_t i = 0; i < cubePositions.size(); i++) {
    auto obj = std::make_shared<GameObject>();

    std::string meshName = "Cube" + std::to_string(i);
    auto mesh = ResourceManager::LoadMesh(meshName, MeshCreator::CreateCube());
    obj->SetMesh(mesh);

    obj->SetMaterial(mat);

    float angle = 20.0f * i;
    obj->transform.SetPosition(cubePositions[i]);
    obj->transform.SetRotation(glm::vec3(angle, angle / 0.3f, angle / 0.5f));

    ObjectManager::Add(obj);
  }
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
