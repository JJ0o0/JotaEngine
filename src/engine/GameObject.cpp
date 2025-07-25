#include "engine/GameObject.hpp"

GameObject::GameObject(const std::string &n) : model(nullptr), name(n) {}

GameObject::~GameObject() = default;

void GameObject::Render(Shader &shader) {
  if (!model)
    return;

  shader.Bind();
  shader.SetMatrix4("model", transform.GetModelMatrix());

  model->Render(shader);

  shader.Unbind();
}

void GameObject::Update(float dt) {}

void GameObject::SetModel(std::shared_ptr<Model> m) { model = m; }

void GameObject::SetName(const std::string &newname) { name = newname; }

std::shared_ptr<Model> GameObject::GetModel() const { return model; }

const std::string &GameObject::GetName() const { return name; }
