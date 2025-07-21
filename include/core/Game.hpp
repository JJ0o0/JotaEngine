#pragma once

#include "core/Window.hpp"
#include "core/Shader.hpp"
#include "core/Mesh.hpp"

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
  Shader *default_shader;
  Mesh *triangle_mesh;
};
