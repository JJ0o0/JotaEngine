#include "core/Window.h"

#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(int w, int h, const char* t) :
    width(w), height(h), title(t) 
{
    if (!glfwInit()) {
        std::cerr << "Não foi possível iniciar o GLFW!" << std::endl;

        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(
        width, height,
        title,
        nullptr, nullptr
    );
    if (!window) {
        std::cerr << "Não foi possível iniciar a janela!" << std::endl;

        glfwTerminate();
        std::exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Não foi possível iniciar o GLAD!" << std::endl;

        std::exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SetMouseLock();

    std::cout << "JotaEngine inicializada com sucesso!\n";
    std::cout << "OpenGL versão: " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::SetShouldClose(bool value) {
    glfwSetWindowShouldClose(window, value);
}

void Window::SetMouseLock() {
    locked = !locked;

    int value = locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
    glfwSetInputMode(window, GLFW_CURSOR, value);
}

void Window::SetMouseCallback(void (*func)(GLFWwindow*, double, double)) {
    glfwSetCursorPosCallback(window, func);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::PollEvents() const {
    glfwPollEvents();
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(window);
}

GLFWwindow* Window::GetGLFWWindow() const {
    return window;
}

float Window::GetAspectRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}