#pragma once

#include "GameObject.hpp"

#include <memory>
#include <vector>
#include <string>

class ObjectManager {
public:
  static void Add(std::shared_ptr<GameObject> object);
  static void Remove(const std::string &name);
  static std::shared_ptr<GameObject> Get(const std::string &name);

  static void Update(float deltaTime);
  static void Render(Camera &camera, float aspectRatio);

private:
  static std::vector<std::shared_ptr<GameObject>> objects;
};
