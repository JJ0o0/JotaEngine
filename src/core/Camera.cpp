#include "core/Camera.h"

#include "glm/ext/matrix_transform.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(2.5f),
      MouseSensitivity(0.1f)
{
    Position = pos;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;

    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraDirection direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == CameraDirection::FORWARD)
        Position += Front * velocity;
    if (direction == CameraDirection::BACKWARD)
        Position -= Front * velocity;
    if (direction == CameraDirection::LEFT)
        Position -= Right * velocity;
    if (direction == CameraDirection::RIGHT)
        Position += Right * velocity;
    if (direction == CameraDirection::UP)
        Position += WorldUp * velocity;
    if (direction == CameraDirection::DOWN)
        Position -= WorldUp * velocity;
}

void Camera::ProcessMouseMovement(float xoff, float yoff, bool constrainPitch) {
    xoff *= MouseSensitivity;
    yoff *= MouseSensitivity;

    Yaw += xoff;
    Pitch += yoff;

    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::GetMouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xoffset = xpos - lastX;
    yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    ProcessMouseMovement(xoffset, yoffset);
}

void Camera::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}