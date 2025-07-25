#pragma once

#include <memory>

#include "core/Shader.hpp"
#include "engine/Model.hpp"
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

  void SetModel(std::shared_ptr<Model> model);

  std::shared_ptr<Model> GetModel() const;

private:
  std::string name;

  std::shared_ptr<Model> model;
};
