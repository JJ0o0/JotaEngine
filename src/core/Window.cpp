#include "core/Window.hpp"
#include "engine/InputManager.hpp"

#include <cstdio>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

Window::Window(int width, int height, const char *title)
    : width(width), height(height), title(title), window(nullptr),
      lastFrameTime(0.0f) {}

Window::~Window() {
  if (window) {
    Terminate();
  }
}

bool Window::Init() {
  if (!glfwInit()) {
    std::cerr << "Não foi possível inicializar o GLFW!\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  // PARA MACOS
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL) {
    std::cerr << "Não foi possível criar a janela!\n";

    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Não foi possível inicializar o GLAD!\n";

    return false;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, InputManager::KeyCallback);

  glEnable(GL_DEPTH_TEST);

  lastFrameTime = static_cast<float>(glfwGetTime());

  std::cout << "Bem vindo a JotaEngine!\n";
  std::cout << "Sistema: " << GetSystemName().c_str() << "\n";
  std::cout << "Versão OpenGL: " << (const char *)glGetString(GL_VERSION)
            << "\n";

  return true;
}

void Window::Terminate() {
  glfwDestroyWindow(window);
  glfwTerminate();

  window = nullptr;
}

float Window::GetDeltaTime() {
  float currTime = static_cast<float>(glfwGetTime());
  float delta = currTime - lastFrameTime;

  lastFrameTime = currTime;
  return delta;
}

void Window::SwapBuffers() const { glfwSwapBuffers(window); }

void Window::PollEvents() const { glfwPollEvents(); }

void Window::SetShouldClose(bool value) {
  glfwSetWindowShouldClose(window, value);
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(window); }

// EU AMO C++
// Ele já converte height para float :D
// Mas, pra deixar mais facil de ler, vou usar static_cast pros dois.
float Window::GetAspectRatio() const {
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);

  return static_cast<float>(w) / static_cast<float>(h);
}

// NÃO ME PERGUNTE COMO ISSO FOI FEITO
// Pergunta pro gpt :D
std::string Window::GetSystemName() {
  char buffer[128];
  std::string result = "";
  FILE *pipe = popen("uname -s", "r");
  if (!pipe)
    return "Desconhecido";

  while (fgets(buffer, sizeof buffer, pipe) != NULL) {
    result += buffer;
  }
  pclose(pipe);

  if (!result.empty() && result[result.size() - 1] == '\n') {
    result.erase(result.size() - 1);
  }

  return result;
}

GLFWwindow *Window::GetNative() const { return window; }

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
