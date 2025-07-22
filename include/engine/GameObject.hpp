#pragma once

#include <memory>

#include "core/Shader.hpp"
#include "core/Mesh.hpp"
#include "core/Texture.hpp"
#include "engine/Transform.hpp"

class GameObject {
public:
  GameObject(const std::string &name = "GameObject");
  ~GameObject();

  const std::string &GetName() const;
  void SetName(const std::string &newName);

  virtual void Render(Shader &shader);
  virtual void Update(float dt);

  Transform transform;

  void SetMesh(std::shared_ptr<Mesh> mesh);
  void SetTexture(std::shared_ptr<Texture> texture);

  std::shared_ptr<Mesh> GetMesh() const;
  std::shared_ptr<Texture> GetTexture() const;

private:
  std::string name;

  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Texture> texture;
};
