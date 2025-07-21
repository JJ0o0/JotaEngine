#include "engine/GameObject.hpp"

GameObject::GameObject() : mesh(nullptr), texture(nullptr) {}

GameObject::~GameObject() = default;

void GameObject::Render(Shader &shader) const {
  if (!mesh || !texture)
    return;

  shader.Bind();

  texture->Bind();
  mesh->Render();
  texture->Unbind();

  shader.Unbind();
}

void GameObject::SetMesh(std::shared_ptr<Mesh> m) { mesh = m; }

void GameObject::SetTexture(std::shared_ptr<Texture> tex) { texture = tex; }

std::shared_ptr<Mesh> GameObject::GetMesh() const { return mesh; }

std::shared_ptr<Texture> GameObject::GetTexture() const { return texture; }
