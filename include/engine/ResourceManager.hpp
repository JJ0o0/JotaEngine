#pragma once

#include "engine/Model.hpp"
#include "engine/Material.hpp"
#include "core/Shader.hpp"

#include <unordered_map>
#include <memory>
#include <string>

// Lorde ResourceManager na parada
class ResourceManager {
public:
  static std::shared_ptr<Shader> LoadShader(const std::string &name,
                                            const std::string &vertexPath,
                                            const std::string &fragmentPath);
  static std::shared_ptr<Mesh>
  LoadMesh(const std::string &name, const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices);
  static std::shared_ptr<Mesh> LoadMesh(const std::string &name,
                                        std::shared_ptr<Mesh> mesh);
  static std::shared_ptr<Texture> LoadTexture(const std::string &name,
                                              const std::string &path);
  static std::shared_ptr<Material> LoadMaterial(const std::string &name,
                                                const std::string &diffusePath,
                                                const std::string &specularPath,
                                                float shininess);
  static std::shared_ptr<Material> LoadMaterial(const std::string &name,
                                                const glm::vec3 &diffuseColor,
                                                const glm::vec3 &specularColor,
                                                float shininess);
  static std::shared_ptr<Material>
  LoadMaterial(const std::string &name, std::shared_ptr<Texture> diffuse,
               std::shared_ptr<Texture> specular, float shininess);

  static std::shared_ptr<Model> LoadModel(const std::string &name,
                                          const std::string &path);

  static std::shared_ptr<Shader> GetShader(const std::string &name);
  static std::shared_ptr<Mesh> GetMesh(const std::string &name);
  static std::shared_ptr<Texture> GetTexture(const std::string &name);
  static std::shared_ptr<Material> GetMaterial(const std::string &name);
  static std::shared_ptr<Model> GetModel(const std::string &name);

  static void UnloadShader(const std::string &name);
  static void UnloadMesh(const std::string &name);
  static void UnloadTexture(const std::string &name);
  static void UnloadMaterial(const std::string &name);
  static void UnloadModel(const std::string &name);

  static void Clear();

private:
  ResourceManager() = delete;

  static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
  static std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
  static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
  static std::unordered_map<std::string, std::shared_ptr<Material>> materials;
  static std::unordered_map<std::string, std::shared_ptr<Model>> models;
};
