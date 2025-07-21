#include "core/Game.hpp"
#include "engine/InputManager.hpp"

Game::Game() : default_shader(nullptr), triangle_mesh(nullptr) {}
Game::~Game() {}

void Game::Start() {
  // Se tiver estranho os vectors, é porque o LazyVim fez a autoformatação do
  // jeito dele...
  // Tipo agora no comentario de cima ^
  std::vector<Vertex> vertices = {Vertex({-0.5f, 0.5f, 0.0f}, {0, 1}),
                                  Vertex({0.5f, 0.5f, 0.0f}, {1, 1}),
                                  Vertex({0.5f, -0.5f, 0.0f}, {1, 0}),
                                  Vertex({-0.5f, -0.5f, 0.0f}, {0, 0})};

  std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

  brick_texture = new Texture("assets/textures/brick_albedo.jpg");
  default_shader = new Shader("shaders/default.vert", "shaders/default.frag");
  triangle_mesh = new Mesh(vertices, indices);
}

void Game::Update(float dt) {}

void Game::Input(Window &window) {
  if (InputManager::IsKeyPressedOnce(GLFW_KEY_ESCAPE)) {
    window.SetShouldClose(true);
  }
}

void Game::Render() {
  default_shader->Bind();
  brick_texture->Bind();
  triangle_mesh->Render();
  default_shader->Unbind();
}

void Game::Quit() {
  delete triangle_mesh;
  delete default_shader;
}
