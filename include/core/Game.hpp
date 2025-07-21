#pragma once

#include "core/Window.hpp"
#include "engine/GameObject.hpp"

class Game {
public:
  Game();
  ~Game();

  void Start();
  void Update(float dt);
  void Input(Window &window);
  void Render();
  void Quit();

private:
  std::shared_ptr<Mesh> square_mesh;
  std::shared_ptr<Texture> brick_texture;

  Shader *default_shader;
  GameObject *square_obj;
};
