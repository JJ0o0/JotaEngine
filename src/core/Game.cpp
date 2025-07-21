#include "core/Game.hpp"
#include "engine/InputManager.hpp"

Game::Game() : square_obj(nullptr), default_shader(nullptr) {}
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

  brick_texture = std::make_shared<Texture>("assets/textures/brick_albedo.jpg");
  square_mesh = std::make_shared<Mesh>(vertices, indices);

  square_obj = new GameObject();
  square_obj->SetMesh(square_mesh);
  square_obj->SetTexture(brick_texture);

  default_shader = new Shader("shaders/default.vert", "shaders/default.frag");
}

void Game::Update(float dt) {}

void Game::Input(Window &window) {
  if (InputManager::IsKeyPressedOnce(GLFW_KEY_ESCAPE)) {
    window.SetShouldClose(true);
  }
}

void Game::Render() { square_obj->Render(*default_shader); }

void Game::Quit() {
  delete square_obj;
  delete default_shader;
}
