#pragma once

#include "core/Shader.hpp"
#include "engine/Light.hpp"

#include <vector>
#include <optional>

class LightManager {
public:
  static LightManager &Get() {
    static LightManager instance;
    return instance;
  }

  static constexpr int MAX_POINT_LIGHTS = 32;
  static constexpr int MAX_SPOT_LIGHTS = 32;

  void CreateDirectionalLight(const DirectionalLight &light);
  void CreateSpotLight(const SpotLight &light);
  void CreatePointLight(const PointLight &light);

  std::optional<DirectionalLight> &GetDirectionalLight();
  std::vector<SpotLight> &GetSpotLights();
  std::vector<PointLight> &GetPointLights();

  void SendToShader(Shader &shader) const;
  void Clear();

private:
  LightManager() = default;
  LightManager(const LightManager &) = delete;
  LightManager &operator=(const LightManager &) = delete;

  std::vector<PointLight> pointLights;
  std::vector<SpotLight> spotLights;

  std::optional<DirectionalLight> directionalLight;
};
