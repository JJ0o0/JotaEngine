#include "engine/GameObject.hpp"

GameObject::GameObject(const std::string &n)
    : mesh(nullptr), material(nullptr), name(n) {}

GameObject::~GameObject() = default;

void GameObject::Render(Shader &shader) {
  if (!mesh || !material)
    return;

  shader.Bind();
  shader.SetMatrix4("model", transform.GetModelMatrix());

  material->ApplyToShader(shader);
  mesh->Render();

  shader.Unbind();
}

void GameObject::Update(float dt) {}

void GameObject::SetMesh(std::shared_ptr<Mesh> m) { mesh = m; }

void GameObject::SetMaterial(std::shared_ptr<Material> mat) { material = mat; }

void GameObject::SetName(const std::string &newname) { name = newname; }

std::shared_ptr<Mesh> GameObject::GetMesh() const { return mesh; }

std::shared_ptr<Material> GameObject::GetMaterial() const { return material; }

const std::string &GameObject::GetName() const { return name; }
