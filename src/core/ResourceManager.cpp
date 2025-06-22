#include "core/ResourceManager.h"
#include "graphics/ModelLoader.h"

#include <iostream>

std::map<std::string, Shader*> ResourceManager::shaders;
std::map<std::string, Texture*> ResourceManager::textures;
std::map<std::string, Model*> ResourceManager::models;

void ResourceManager::LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    shaders[name] = new Shader(vertexPath, fragmentPath);
}

Shader* ResourceManager::GetShader(const std::string& name) {
    return shaders[name];
}

void ResourceManager::LoadTexture(const std::string& name, const std::string& filePath) {
    textures[name] = new Texture(filePath);
}

Texture* ResourceManager::GetTexture(const std::string& name) {
    return textures[name];
}

void ResourceManager::LoadModel(const std::string& name, const std::string& path) {
    if (models.count(name) > 0) return;

    Model* model = ModelLoader::LoadModel(path);
    if (model) {
        models[name] = model;
    } else {
        std::cerr << "Erro ao carregar modelo \"" << name << "\" de \"" << path << "\"" << std::endl;
    }
}

Model* ResourceManager::GetModel(const std::string& name) {
    if (models.count(name) == 0) return nullptr;
    return models[name];
}

void ResourceManager::Cleanup() {
    for (auto& s : shaders) delete s.second;
    for (auto& t : textures) delete t.second;
    for (auto& [_, m] : models) delete m;
    
    shaders.clear();
    textures.clear();
    models.clear();
}