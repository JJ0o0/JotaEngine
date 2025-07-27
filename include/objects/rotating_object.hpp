#pragma once

#include "engine/GameObject.hpp"

class RotatingObject : public GameObject {
public:
  RotatingObject();

  void Update(float dt) override;
};
