#pragma once

#include "core/Shader.hpp"
#include "core/Texture.hpp"

#include <memory>
#include <glm/glm.hpp>

struct Material {
  std::shared_ptr<Texture> DiffuseTexture;
  std::shared_ptr<Texture> SpecularTexture;

  glm::vec3 DiffuseColor;
  glm::vec3 SpecularColor;

  float Shininess;
  bool UseTexture;

  Material(std::shared_ptr<Texture> d, std::shared_ptr<Texture> s, float shi)
      : DiffuseTexture(d), SpecularTexture(s), DiffuseColor(0.0f),
        SpecularColor(0.0f), Shininess(shi), UseTexture(true) {}

  Material(const glm::vec3 &d, const glm::vec3 &s, float shi)
      : DiffuseColor(d), SpecularColor(s), DiffuseTexture(nullptr),
        SpecularTexture(nullptr), Shininess(shi), UseTexture(false) {}

  void ApplyToShader(const Shader &shader) {
    if (shader.GetUniformLocation("material.useTexture", true) == -1) {
      return;
    }

    shader.SetFloat("material.shininess", Shininess);
    shader.SetInt("material.useTexture", int(UseTexture));

    if (!UseTexture) {
      shader.SetVec3("material.diffuseColor", DiffuseColor);
      shader.SetVec3("material.specularColor", SpecularColor);
    } else {
      DiffuseTexture->Bind(0);
      shader.SetInt("material.diffuse", 0);

      SpecularTexture->Bind(1);
      shader.SetInt("material.specular", 1);
    }
  }
};
