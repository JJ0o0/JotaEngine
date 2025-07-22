#pragma once

#include "core/Window.hpp"
#include "core/Shader.hpp"
#include "engine/Camera.hpp"

#include <memory>

class Game {
public:
  Game(Window &game_window);
  ~Game();

  void Start();
  void Update(float dt);
  void Input();
  void Render();
  void Quit();

private:
  Window &game_window;

  Camera camera;

  std::shared_ptr<Shader> default_shader;
};
