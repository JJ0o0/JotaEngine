#pragma once

#include "engine/Vertex.hpp"

#include <vector>

class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<unsigned int> &indices);
  ~Mesh();

  void Render() const;
  void Destroy();

private:
  unsigned int VAO, VBO, EBO;

  void Setup();
};
