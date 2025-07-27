#include "objects/rotating_object.hpp"
#include <cmath>

RotatingObject::RotatingObject() {}

void RotatingObject::Update(float dt) {
  float rotationSpeed = 90.0f;
  glm::vec3 currRotation = transform.GetRotation();

  currRotation.y += rotationSpeed * dt;
  currRotation.y = std::fmod(currRotation.y, 360.0f);

  transform.SetRotation(currRotation);
}
