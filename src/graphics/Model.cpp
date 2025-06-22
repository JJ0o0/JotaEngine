#include "graphics/Model.h"

Model::Model(const std::vector<Mesh*>& meshes) : meshes(meshes) {}

Model::~Model() {
    for (Mesh* mesh : meshes)
        delete mesh;
}

void Model::Draw(Shader* shader) {
    for (Mesh* mesh : meshes)
        mesh->Draw(shader);
}