#include "engine/ObjectManager.hpp"

#include <algorithm>

std::vector<std::shared_ptr<GameObject>> ObjectManager::objects;

void ObjectManager::Add(std::shared_ptr<GameObject> object) {
  objects.push_back(object);
}

void ObjectManager::Remove(const std::string &name) {
  objects.erase(
      std::remove_if(objects.begin(), objects.end(),
                     [&](const auto &obj) { return obj->GetName() == name; }),
      objects.end());
}

std::shared_ptr<GameObject> ObjectManager::Get(const std::string &name) {
  for (auto &obj : objects) {
    if (obj->GetName() == name)
      return obj;
  }
  return nullptr;
}

void ObjectManager::Update(float deltaTime) {
  for (auto &obj : objects) {
    obj->Update(deltaTime);
  }
}

void ObjectManager::Render(Shader &shader) {
  for (auto &obj : objects) {
    obj->Render(shader);
  }
}
