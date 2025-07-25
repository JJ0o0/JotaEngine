#include "engine/Model.hpp"

Model::Model() = default;
Model::~Model() = default;

void Model::AddMesh(std::shared_ptr<Mesh> mesh) { meshes.push_back(mesh); }

void Model::AddMaterial(std::shared_ptr<Material> material) {
  materials.push_back(material);
}

std::vector<std::shared_ptr<Mesh>> &Model::GetMeshes() { return meshes; }

std::vector<std::shared_ptr<Material>> &Model::GetMaterials() {
  return materials;
}

void Model::Render(Shader &shader) {
  for (size_t i = 0; i < meshes.size(); i++) {
    if (i < materials.size() && materials[i]) {
      materials[i]->ApplyToShader(shader);
    }

    if (meshes[i]) {
      meshes[i]->Render();
    }
  }
}
