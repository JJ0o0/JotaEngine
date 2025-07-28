#pragma once

#include <memory>

#include "core/Shader.hpp"
#include "engine/Camera.hpp"
#include "engine/Model.hpp"
#include "engine/Transform.hpp"

class GameObject {
public:
  GameObject(const std::string &name = "GameObject");
  ~GameObject();

  Transform transform;

  virtual void Render(Camera &camera, float aspectRatio);
  virtual void Update(float dt);

  void SetName(const std::string &newName);
  void SetModel(std::shared_ptr<Model> model);
  void SetShader(std::shared_ptr<Shader> shader);

  const std::string &GetName() const;
  std::shared_ptr<Model> GetModel() const;
  std::shared_ptr<Shader> GetShader() const;

private:
  std::string name;

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;
};
