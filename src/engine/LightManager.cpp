#include "engine/LightManager.hpp"

void LightManager::CreateDirectionalLight(const DirectionalLight &light) {
  directionalLight = light;
}

void LightManager::CreateSpotLight(const SpotLight &light) {
  if (spotLights.size() < MAX_SPOT_LIGHTS) {
    spotLights.push_back(light);
  }
}

void LightManager::CreatePointLight(const PointLight &light) {
  if (pointLights.size() < MAX_POINT_LIGHTS) {
    pointLights.push_back(light);
  }
}

std::optional<DirectionalLight> &LightManager::GetDirectionalLight() {
  return directionalLight;
}
std::vector<SpotLight> &LightManager::GetSpotLights() { return spotLights; }
std::vector<PointLight> &LightManager::GetPointLights() { return pointLights; }

void LightManager::SendToShader(Shader &shader) const {
  shader.SetInt("pointLightsQuantity", pointLights.size());
  shader.SetInt("spotLightsQuantity", spotLights.size());

  for (int i = 0; i < pointLights.size(); i++) {
    const auto &light = pointLights[i];
    std::string lightName = "pointLights[" + std::to_string(i) + "]";

    shader.SetVec3(lightName + ".ambient", light.Base.Ambient);
    shader.SetVec3(lightName + ".diffuse", light.Base.Diffuse);
    shader.SetVec3(lightName + ".specular", light.Base.Specular);

    shader.SetVec3(lightName + ".position", light.Position);

    shader.SetFloat(lightName + ".constant", light.Constant);
    shader.SetFloat(lightName + ".linear", light.Linear);
    shader.SetFloat(lightName + ".quadratic", light.Quadratic);
  }

  for (int i = 0; i < spotLights.size(); i++) {
    const auto &light = spotLights[i];
    std::string lightName = "spotLights[" + std::to_string(i) + "]";

    shader.SetVec3(lightName + ".ambient", light.Base.Ambient);
    shader.SetVec3(lightName + ".diffuse", light.Base.Diffuse);
    shader.SetVec3(lightName + ".specular", light.Base.Specular);

    shader.SetVec3(lightName + ".position", light.Position);
    shader.SetVec3(lightName + ".direction", light.Direction);

    shader.SetFloat(lightName + ".constant", light.Constant);
    shader.SetFloat(lightName + ".linear", light.Linear);
    shader.SetFloat(lightName + ".quadratic", light.Quadratic);

    shader.SetFloat(lightName + ".cutOff", light.CutOff);
    shader.SetFloat(lightName + ".outerCutOff", light.OuterCutOff);
  }

  if (directionalLight.has_value()) {
    const auto &light = directionalLight.value();

    shader.SetVec3("directionalLight.ambient", light.Base.Ambient);
    shader.SetVec3("directionalLight.diffuse", light.Base.Diffuse);
    shader.SetVec3("directionalLight.specular", light.Base.Specular);
    shader.SetVec3("directionalLight.direction", light.Direction);
  } else {
    shader.SetVec3("directionalLight.ambient", glm::vec3(0.0f));
    shader.SetVec3("directionalLight.diffuse", glm::vec3(0.0f));
    shader.SetVec3("directionalLight.specular", glm::vec3(0.0f));
  }
}

void LightManager::Clear() {
  spotLights.clear();
  pointLights.clear();
  directionalLight.reset();
}
