#include "engine/Transform.hpp"
#include "glm/ext/matrix_transform.hpp"

Transform::Transform() : position(0.0f), rotation(0.0f), scale(1.0f) {}
Transform::~Transform() = default;

glm::mat4 Transform::GetModelMatrix() const {
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::translate(trans, position);

  glm::mat4 rot = glm::mat4(1.0f);
  rot = glm::rotate(rot, glm::radians(rotation.y),
                    glm::vec3(0.0f, 1.0f, 0.0f)); // YAW
  rot = glm::rotate(rot, glm::radians(rotation.x),
                    glm::vec3(1.0f, 0.0f, 0.0f)); // PITCH
  rot = glm::rotate(rot, glm::radians(rotation.z),
                    glm::vec3(0.0f, 0.0f, 1.0f)); // ROLL

  glm::mat4 sca = glm::mat4(1.0f);
  sca = glm::scale(sca, scale);

  return trans * rot * sca;
}
