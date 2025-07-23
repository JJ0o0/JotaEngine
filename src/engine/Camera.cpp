#include "engine/Camera.hpp"
#include "engine/InputManager.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <cmath>

Camera::Camera()
    : position(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f),
      world_up(0.0f, 1.0f, 0.0f), yaw(-90.0f), pitch(0.0f) {
  UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(front);

  right = glm::normalize(glm::cross(front, world_up));
  up = glm::normalize(glm::cross(right, front));
}

void Camera::KeyboardMovement(float delta) {
  float speed;

  if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
    speed = 5.0f;
  } else {
    speed = 2.5f;
  }

  float velocity = speed * delta;

  if (InputManager::IsKeyPressed(GLFW_KEY_W)) {
    position += velocity * front;
  } else if (InputManager::IsKeyPressed(GLFW_KEY_S)) {
    position -= velocity * front;
  }

  if (InputManager::IsKeyPressed(GLFW_KEY_D)) {
    position += velocity * right;
  } else if (InputManager::IsKeyPressed(GLFW_KEY_A)) {
    position -= velocity * right;
  }

  if (InputManager::IsKeyPressed(GLFW_KEY_SPACE)) {
    position += velocity * world_up;
  } else if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
    position -= velocity * world_up;
  }
}

void Camera::MouseMovement() {
  float xoffset = InputManager::GetMouseXOffset();
  float yoffset = InputManager::GetMouseYOffset();

  float sensivity = 0.1f;
  xoffset *= sensivity;
  yoffset *= sensivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f) {
    pitch = 89.0f;
  }
  if (pitch < -89.0f) {
    pitch = -89.0f;
  }

  UpdateCameraVectors();
}

glm::vec3 Camera::GetPosition() const { return position; }

glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
  return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}
