#include "engine/ResourceManager.hpp"

std::unordered_map<std::string, std::shared_ptr<Shader>>
    ResourceManager::shaders;
std::unordered_map<std::string, std::shared_ptr<Mesh>> ResourceManager::meshes;
std::unordered_map<std::string, std::shared_ptr<Texture>>
    ResourceManager::textures;

std::shared_ptr<Shader>
ResourceManager::LoadShader(const std::string &name,
                            const std::string &vertexPath,
                            const std::string &fragmentPath) {
  auto i = shaders.find(name);

  if (i != shaders.end()) {
    return i->second;
  }

  auto s = std::make_shared<Shader>(vertexPath, fragmentPath);
  shaders[name] = s;

  return s;
}

std::shared_ptr<Mesh>
ResourceManager::LoadMesh(const std::string &name,
                          const std::vector<Vertex> &vertices,
                          const std::vector<unsigned int> &indices) {
  auto i = meshes.find(name);

  if (i != meshes.end()) {
    return i->second;
  }

  auto m = std::make_shared<Mesh>(vertices, indices);
  meshes[name] = m;

  return m;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string &name,
                                                      const std::string &path) {
  auto i = textures.find(name);

  if (i != textures.end()) {
    return i->second;
  }

  auto t = std::make_shared<Texture>(path.c_str());
  textures[name] = t;

  return t;
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string &name) {
  auto i = shaders.find(name);

  if (i != shaders.end()) {
    return i->second;
  }

  return nullptr;
}

std::shared_ptr<Mesh> ResourceManager::GetMesh(const std::string &name) {
  auto i = meshes.find(name);

  if (i != meshes.end()) {
    return i->second;
  }

  return nullptr;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string &name) {
  auto i = textures.find(name);

  if (i != textures.end()) {
    return i->second;
  }

  return nullptr;
}

void ResourceManager::UnloadShader(const std::string &name) {
  auto i = shaders.find(name);

  if (i != shaders.end()) {
    shaders.erase(i);
  }
}

void ResourceManager::UnloadMesh(const std::string &name) {
  auto i = meshes.find(name);

  if (i != meshes.end()) {
    meshes.erase(i);
  }
}

void ResourceManager::UnloadTexture(const std::string &name) {
  auto i = textures.find(name);

  if (i != textures.end()) {
    textures.erase(i);
  }
}

void ResourceManager::Clear() {
  shaders.clear();
  meshes.clear();
  textures.clear();
}
