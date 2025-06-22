#pragma once

#include <string>
#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
private:
    unsigned int shaderProgram;

    std::string ReadFile(const std::string& path);

    unsigned int CompileShader(unsigned int type, const char* source);
    void CheckCompileErrors(unsigned int shader, const std::string& type);
public:
    Shader(const std::string& vertexPath, const std::string fragPath);
    ~Shader();

    void Use() const;
    void SetUniform1i(const std::string& name, int value) const;
    void SetUniform1f(const std::string& name, float value) const;
    void SetUniformVec3(const std::string& name, glm::vec3 value) const;
    void SetUniformMat4(const std::string& name, glm::mat4 value) const;

    unsigned int Program() const { return shaderProgram; }
};