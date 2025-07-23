#pragma once

#include <glm/glm.hpp>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;

  Vertex() = default;
  Vertex(const glm::vec3 &pos, const glm::vec3 &norm,
         const glm::vec2 &texCoords)
      : Position(pos), Normal(norm), TexCoords(texCoords) {}
};
