#pragma once

#include <glm/glm.hpp>

class Transform {
public:
  Transform();
  ~Transform();

  void SetPosition(const glm::vec3 &pos) { position = pos; }
  void SetRotation(const glm::vec3 &rot) { rotation = rot; }
  void SetScale(const glm::vec3 &sca) { scale = sca; }

  glm::vec3 GetPosition() const { return position; }
  glm::vec3 GetRotation() const { return rotation; }
  glm::vec3 GetScale() const { return scale; }
  glm::mat4 GetModelMatrix() const;

private:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};
