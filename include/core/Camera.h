#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include <GLFW/glfw3.h>

enum class CameraDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Pitch, Yaw;
    float xoffset = 0.0f, yoffset = 0.0f;
    float lastX = 400, lastY = 300;
    bool firstMouse = true;
    float MovementSpeed, MouseSensitivity;

    Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(CameraDirection direction, float deltaTime);
    void ProcessMouseMovement(float xoff, float yoff, bool constrainPitch=true);

    void GetMouseCallback(GLFWwindow* window, double xpos, double ypos);
private:
    void UpdateCameraVectors();
};