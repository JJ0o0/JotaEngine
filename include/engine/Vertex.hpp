#pragma once

#include <glm/glm.hpp>

struct Vertex {
  glm::vec3 Position;

  Vertex() = default;
  Vertex(const glm::vec3 &pos) : Position(pos) {}
};
