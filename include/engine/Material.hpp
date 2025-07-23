#pragma once

#include "core/Shader.hpp"
#include "core/Texture.hpp"

#include <memory>
#include <glm/glm.hpp>

struct Material {
  std::shared_ptr<Texture> Diffuse;
  std::shared_ptr<Texture> Specular;
  float Shininess;

  Material(std::shared_ptr<Texture> d, std::shared_ptr<Texture> s, float shi)
      : Diffuse(d), Specular(s), Shininess(shi) {}

  void ApplyToShader(const Shader &shader) {
    Diffuse->Bind(0);
    shader.SetInt("material.diffuse", 0);

    Specular->Bind(1);
    shader.SetInt("material.specular", 1);

    shader.SetFloat("material.shininess", Shininess);
  }
};
