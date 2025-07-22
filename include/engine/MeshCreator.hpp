#pragma once

#include "core/Mesh.hpp"

#include <memory>

class MeshCreator {
public:
  static std::shared_ptr<Mesh> CreatePlane();
  static std::shared_ptr<Mesh> CreateCube();
};
