#pragma once

#include <map>
#include <string>

#include "graphics/Shader.h"
#include "graphics/Model.h"
#include "graphics/Texture.h"

class ResourceManager {
public:
    static void LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    static Shader* GetShader(const std::string& name);

    static void LoadTexture(const std::string& name, const std::string& filePath);
    static Texture* GetTexture(const std::string& name);

    static void LoadModel(const std::string& name, const std::string& filePath);
    static Model* GetModel(const std::string& name);

    static void Cleanup();
private:
    static std::map<std::string, Shader*> shaders;
    static std::map<std::string, Texture*> textures;
    static std::map<std::string, Model*> models;
};