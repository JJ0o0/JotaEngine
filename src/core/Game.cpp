#include "core/Game.hpp"

#include "engine/GameObject.hpp"
#include "engine/GameObjectifier.hpp"
#include "engine/InputManager.hpp"
#include "engine/Light.hpp"
#include "engine/ObjectManager.hpp"
#include "engine/MeshCreator.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/LightManager.hpp"

#include "objects/rotating_object.hpp"

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

void Game::StartMaterials() {
  ResourceManager::LoadMaterial("ground_material", glm::vec3(0.8f),
                                glm::vec3(1.0f), 16.0f);

  ResourceManager::LoadMaterial("cube_material", glm::vec3(0.75f, 0.0f, 0.25f),
                                glm::vec3(0.3f), 32.0f);
}

void Game::StartObjects() {
  ResourceManager::LoadMesh("ground_mesh", MeshCreator::CreatePlane());
  ResourceManager::LoadMesh("cube_mesh", MeshCreator::CreateCube());

  auto obj = GameObjectifier::MakeObject<GameObject>("ground", "ground_mesh",
                                                     "ground_material");
  auto cubeObj = GameObjectifier::MakeObject<GameObject>("cube", "cube_mesh",
                                                         "cube_material");
  auto loadedObj = GameObjectifier::MakeObject<GameObject>(
      "loaded", "assets/models/monkey.glb");
  auto loadedTexturedObj = GameObjectifier::MakeObject<RotatingObject>(
      "loaded_textured", "assets/models/backpack/backpack.obj");

  obj->transform.SetPosition(glm::vec3(0.0f, -5.0f, 0.0f));
  obj->transform.SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
  obj->transform.SetScale(glm::vec3(10.0f));

  cubeObj->transform.SetPosition(glm::vec3(3.5f, -4.5f, 1.0f));
  cubeObj->transform.SetRotation(glm::vec3(0.0f, 25.0f, 0.0f));

  loadedObj->transform.SetPosition(glm::vec3(0.0f, -4.0f, -3.0f));
  loadedObj->transform.SetScale(glm::vec3(1.5f, 0.5f, 1.0f));

  loadedTexturedObj->transform.SetPosition(glm::vec3(0.0f, -3.5f, 2.0f));
  loadedTexturedObj->transform.SetScale(glm::vec3(0.5f));

  ObjectManager::Add(obj);
  ObjectManager::Add(cubeObj);
  ObjectManager::Add(loadedObj);
  ObjectManager::Add(loadedTexturedObj);
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
