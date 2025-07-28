#include "engine/GameObject.hpp"

GameObject::GameObject(const std::string &n)
    : model(nullptr), shader(nullptr), name(n) {}

GameObject::~GameObject() = default;

void GameObject::Render(Camera &camera, float aspectRatio) {
  if (!model)
    return;

  shader->Bind();
  shader->SetMatrix4("model", transform.GetModelMatrix());
  shader->SetMatrix4("view", camera.GetViewMatrix());
  shader->SetMatrix4("projection", camera.GetProjectionMatrix(aspectRatio));

  if (shader->GetUniformLocation("viewPos", true) != -1) {
    shader->SetVec3("viewPos", camera.GetPosition());
  }

  model->Render(*shader);

  shader->Unbind();
}

void GameObject::Update(float dt) {}

void GameObject::SetShader(std::shared_ptr<Shader> s) { shader = s; }

void GameObject::SetModel(std::shared_ptr<Model> m) { model = m; }

void GameObject::SetName(const std::string &newname) { name = newname; }

std::shared_ptr<Shader> GameObject::GetShader() const { return shader; }

std::shared_ptr<Model> GameObject::GetModel() const { return model; }

const std::string &GameObject::GetName() const { return name; }
