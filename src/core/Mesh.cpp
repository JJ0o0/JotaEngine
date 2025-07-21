#include "core/Mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex> &verts,
           const std::vector<unsigned int> &inds)
    : vertices(verts), indices(inds) {
  Setup();
}
Mesh::~Mesh() { Destroy(); }

void Mesh::Setup() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

void Mesh::Destroy() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  VAO = 0;
  VBO = 0;
  EBO = 0;
}

void Mesh::Render() const {
  glBindVertexArray(VAO);
  // Toda vez que tu ver static_cast, saiba que eu nn sei o que djabo to
  // fazendo...
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
