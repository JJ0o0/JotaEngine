#pragma once

#include "engine/Model.hpp"

#include <memory>
#include <string>

class MeshCreator {
public:
  static std::shared_ptr<Mesh> CreatePlane();
  static std::shared_ptr<Mesh> CreateCube();

  static std::shared_ptr<Model> LoadModel(const std::string &path);

private:
  static std::string GetFileName(const std::string &path);
};
