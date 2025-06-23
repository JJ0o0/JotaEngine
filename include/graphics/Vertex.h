#pragma once

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    Vertex(
        const glm::vec3& pos = {}, 
        const glm::vec3& norm = {}, 
        const glm::vec2& tex = glm::vec2(0.0f, 0.0f),
        const glm::vec3& tangent = {},
        const glm::vec3& bitangent = {}
    ) : Position(pos), TexCoords(tex), Normal(norm), 
        Tangent(tangent), Bitangent(bitangent) {}
};