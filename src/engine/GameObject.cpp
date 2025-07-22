#include "engine/GameObject.hpp"

GameObject::GameObject(const std::string &n)
    : mesh(nullptr), texture(nullptr), name(n) {}

GameObject::~GameObject() = default;

void GameObject::Render(Shader &shader) {
  if (!mesh || !texture)
    return;

  shader.Bind();
  shader.SetMatrix4("model", transform.GetModelMatrix());

  texture->Bind();
  mesh->Render();
  texture->Unbind();

  shader.Unbind();
}

void GameObject::Update(float dt) {}

void GameObject::SetMesh(std::shared_ptr<Mesh> m) { mesh = m; }

void GameObject::SetTexture(std::shared_ptr<Texture> tex) { texture = tex; }

void GameObject::SetName(const std::string &newname) { name = newname; }

std::shared_ptr<Mesh> GameObject::GetMesh() const { return mesh; }

std::shared_ptr<Texture> GameObject::GetTexture() const { return texture; }

const std::string &GameObject::GetName() const { return name; }
