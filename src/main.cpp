#include "core/Window.hpp"
#include "core/Game.hpp"

int main() {
  Window window(800, 800, "JotaEngine");
  if (!window.Init()) {
    return -1;
  }

  Game game;
  game.Start();

  while (!window.ShouldClose()) {
    float deltatime = window.GetDeltaTime();

    game.Input(window);
    game.Update(deltatime);

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    game.Render();

    window.SwapBuffers();
    window.PollEvents();
  }

  window.Terminate();
  game.Quit();

  return 0;
}
