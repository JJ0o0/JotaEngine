#pragma once

#include "Mesh.h"

#include <vector>

class Model {
public:
    Model(const std::vector<Mesh*>& meshes);
    ~Model();

    void Draw(Shader* shader);
private:
    std::vector<Mesh*> meshes;
};