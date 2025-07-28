#pragma once

#include "engine/GameObject.hpp"
#include "engine/ResourceManager.hpp"

#include <memory>
#include <string>

class GameObjectifier {
public:
  template <typename T>
  static std::shared_ptr<T> MakeObject(const std::string &name,
                                       const std::string &path,
                                       const std::string &shader) {
    static_assert(std::is_base_of<GameObject, T>::value,
                  "T tem que herdar de GameObject.");
    auto obj = std::make_shared<T>();

    auto model = ResourceManager::LoadModel(name, path);
    auto sha = ResourceManager::GetShader(shader);

    obj->SetModel(model);
    obj->SetShader(sha);

    return obj;
  }

  template <typename T>
  static std::shared_ptr<T>
  MakeObject(const std::string &name, const std::string &meshRefName,
             const std::string &materialRefName, const std::string &shader) {
    static_assert(std::is_base_of<GameObject, T>::value,
                  "T tem que herdar de GameObject.");

    auto obj = std::make_shared<T>();

    auto mesh = ResourceManager::GetMesh(meshRefName);
    auto material = ResourceManager::GetMaterial(materialRefName);

    auto model = ResourceManager::LoadModel(name, mesh, material);
    auto sha = ResourceManager::GetShader(shader);

    obj->SetModel(model);
    obj->SetShader(sha);

    return obj;
  }
};
