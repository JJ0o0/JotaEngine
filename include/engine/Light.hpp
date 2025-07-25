#pragma once

#include <cmath>
#include <glm/glm.hpp>

struct BaseLight {
  glm::vec3 Ambient;
  glm::vec3 Diffuse;
  glm::vec3 Specular;

  BaseLight(const glm::vec3 &ambient, const glm::vec3 &diffuse,
            const glm::vec3 &specular)
      : Ambient(ambient), Diffuse(diffuse), Specular(specular) {}
};

struct DirectionalLight {
  BaseLight Base;

  glm::vec3 Direction;

  DirectionalLight(const BaseLight &base_light, const glm::vec3 &direction)
      : Base(base_light), Direction(direction) {}

  void SetDirection(const glm::vec3 &direction) { Direction = direction; }
};

struct PointLight {
  BaseLight Base;

  glm::vec3 Position;

  float Range;

  float Constant;
  float Linear;
  float Quadratic;

  PointLight(const BaseLight &base_light, const glm::vec3 &position,
             float range)
      : Base(base_light), Position(position), Range(range) {
    Constant = 1.0f;
    Linear = 4.5f / range;
    Quadratic = 75.0f / (range * range);
  }

  void SetPosition(const glm::vec3 &position) { Position = position; }

  void SetRange(float target) {
    Range = target;

    Constant = 1.0f;
    Linear = 4.5f / Range;
    Quadratic = 75.0f / (Range * Range);
  }
};

struct SpotLight {
  BaseLight Base;

  glm::vec3 Position;
  glm::vec3 Direction;

  float Range;

  float Constant;
  float Linear;
  float Quadratic;

  float CutOff;
  float OuterCutOff;

  SpotLight(const BaseLight &base_light, const glm::vec3 &position,
            const glm::vec3 &direction, float range, float innerAngleDeg,
            float outerAngleDeg)
      : Base(base_light), Position(position), Direction(direction),
        Range(range) {
    Constant = 1.0f;
    Linear = 4.5f / range;
    Quadratic = 75.0f / (range * range);

    CutOff = std::cos(glm::radians(innerAngleDeg));
    OuterCutOff = std::cos(glm::radians(outerAngleDeg));
  }

  void SetDirection(const glm::vec3 &direction) { Direction = direction; }

  void SetPosition(const glm::vec3 &position) { Position = position; }

  void SetRange(float target) {
    Range = target;

    Constant = 1.0f;
    Linear = 4.5f / Range;
    Quadratic = 75.0f / (Range * Range);
  }

  void SetAngles(float inner, float outer) {
    CutOff = std::cos(glm::radians(inner));
    OuterCutOff = std::cos(glm::radians(outer));
  }
};
