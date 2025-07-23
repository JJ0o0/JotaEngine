#pragma once

#include <glm/glm.hpp>

class Camera {
public:
  Camera();

  void UpdateCameraVectors();

  void KeyboardMovement(float delta);
  void MouseMovement();

  glm::vec3 GetPosition() const;
  glm::vec3 GetFront() const;

  glm::mat4 GetViewMatrix() const;
  glm::mat4 GetProjectionMatrix(float aspectRatio) const;

private:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 world_up;

  float yaw;
  float pitch;
};
