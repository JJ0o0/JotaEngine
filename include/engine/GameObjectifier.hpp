#pragma once

#include "engine/GameObject.hpp"
#include "engine/ResourceManager.hpp"

#include <memory>
#include <string>

class GameObjectifier {
public:
  template <typename T>
  static std::shared_ptr<T> MakeObject(const std::string &name,
                                       const std::string &path) {
    static_assert(std::is_base_of<GameObject, T>::value,
                  "T tem que herdar de GameObject.");
    auto obj = std::make_shared<T>();

    auto model = ResourceManager::LoadModel(name, path);

    obj->SetModel(model);

    return obj;
  }

  template <typename T>
  static std::shared_ptr<T> MakeObject(const std::string &name,
                                       const std::string &meshRefName,
                                       const std::string &materialRefName) {
    static_assert(std::is_base_of<GameObject, T>::value,
                  "T tem que herdar de GameObject.");

    auto obj = std::make_shared<T>();

    auto mesh = ResourceManager::GetMesh(meshRefName);
    auto material = ResourceManager::GetMaterial(materialRefName);

    auto model = ResourceManager::LoadModel(name, mesh, material);

    obj->SetModel(model);

    return obj;
  }
};
