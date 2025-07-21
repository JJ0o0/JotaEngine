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
  std::shared_ptr<Shader> default_shader;
  std::shared_ptr<GameObject> square_obj;
};
