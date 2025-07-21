#pragma once

#include <memory>

#include "core/Shader.hpp"
#include "core/Mesh.hpp"
#include "core/Texture.hpp"
#include "engine/Transform.hpp"

class GameObject {
public:
  GameObject();
  ~GameObject();

  void Render(Shader &shader) const;

  Transform transform;

  void SetMesh(std::shared_ptr<Mesh> mesh);
  void SetTexture(std::shared_ptr<Texture> texture);

  std::shared_ptr<Mesh> GetMesh() const;
  std::shared_ptr<Texture> GetTexture() const;

private:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Texture> texture;
};
