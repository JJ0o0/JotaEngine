#pragma once

#include "core/Mesh.hpp"
#include "engine/Material.hpp"

#include "core/Shader.hpp"
#include <memory>
#include <vector>

class Model {
public:
  Model();
  ~Model();

  void AddMesh(std::shared_ptr<Mesh> mesh);
  void AddMaterial(std::shared_ptr<Material> material);

  std::vector<std::shared_ptr<Mesh>> &GetMeshes();
  std::vector<std::shared_ptr<Material>> &GetMaterials();

  void Render(Shader &shader);

private:
  std::vector<std::shared_ptr<Mesh>> meshes;
  std::vector<std::shared_ptr<Material>> materials;
};
