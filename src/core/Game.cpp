#include "core/Game.hpp"
#include "engine/InputManager.hpp"
#include "engine/ResourceManager.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Game::Game() = default;
Game::~Game() = default;

void Game::Start() {
  // Se tiver estranho os vectors, é porque o LazyVim fez a autoformatação do
  // jeito dele...
  // Tipo agora no comentario de cima ^
  std::vector<Vertex> vertices = {Vertex({-0.5f, 0.5f, 0.0f}, {0, 1}),
                                  Vertex({0.5f, 0.5f, 0.0f}, {1, 1}),
                                  Vertex({0.5f, -0.5f, 0.0f}, {1, 0}),
                                  Vertex({-0.5f, -0.5f, 0.0f}, {0, 0})};

  std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

  square_obj = std::make_unique<GameObject>();
  square_obj->SetMesh(ResourceManager::LoadMesh("Plane", vertices, indices));
  square_obj->SetTexture(ResourceManager::LoadTexture(
      "BrickAlbedo", "assets/textures/brick_albedo.jpg"));

  default_shader = ResourceManager::LoadShader(
      "Default", "shaders/default.vert", "shaders/default.frag");
}

void Game::Update(float dt) {
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glm::mat4 projection;
  projection =
      glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);

  default_shader->Bind();
  default_shader->SetMatrix4("view", view);
  default_shader->SetMatrix4("projection", projection);
}

void Game::Input(Window &window) {
  if (InputManager::IsKeyPressedOnce(GLFW_KEY_ESCAPE)) {
    window.SetShouldClose(true);
  }
}

void Game::Render() { square_obj->Render(*default_shader); }

void Game::Quit() { ResourceManager::Clear(); }
