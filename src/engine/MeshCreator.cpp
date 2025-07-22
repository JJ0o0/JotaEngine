#include "engine/MeshCreator.hpp"

std::shared_ptr<Mesh> MeshCreator::CreatePlane() {
  std::vector<Vertex> vertices = {{{-0.5f, 0.5f, 0.0f}, {0, 1}},
                                  {{0.5f, 0.5f, 0.0f}, {1, 1}},
                                  {{0.5f, -0.5f, 0.0f}, {1, 0}},
                                  {{-0.5f, -0.5f, 0.0f}, {0, 0}}};

  std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

  return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> MeshCreator::CreateCube() {
  std::vector<Vertex> vertices = {
      // Frente
      {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
      {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
      {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},

      // Traseira
      {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
      {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
      {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},

      // Esquerda
      {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
      {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
      {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
      {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},

      // Direita
      {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
      {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
      {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},

      // Cima
      {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
      {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
      {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
      {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},

      // Baixo
      {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
      {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
      {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}},
      {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}},
  };

  std::vector<unsigned int> indices = {
      0,  1,  2,  2,  3,  0,  // Frente
      4,  5,  6,  6,  7,  4,  // Traseira
      8,  9,  10, 10, 11, 8,  // Esquerda
      12, 13, 14, 14, 15, 12, // Direita
      16, 17, 18, 18, 19, 16, // Cima
      20, 21, 22, 22, 23, 20  // Baixo
  };

  return std::make_shared<Mesh>(vertices, indices);
}
