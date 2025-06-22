#pragma once

#include "Vertex.h"
#include "Shader.h"

#include <vector>

class Mesh {
private:
    unsigned int VAO, VBO, EBO;
    size_t indexCount;
    
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void Setup();
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Draw(Shader* shader);
};