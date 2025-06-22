#include "graphics/Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string fragPath) {
    std::string vertexCode = ReadFile(vertexPath);
    std::string fragCode = ReadFile(fragPath);
    
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    unsigned int fragShader = CompileShader(GL_FRAGMENT_SHADER, fragCode.c_str());
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    
    CheckCompileErrors(shaderProgram, "PROGRAM");
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::Use() const {
    glUseProgram(shaderProgram);
}

void Shader::SetUniform1i(const std::string& name, int value) const {
    glUniform1i(
        glGetUniformLocation(shaderProgram, name.c_str()),
        value
    );
}

void Shader::SetUniform1f(const std::string& name, float value) const {
    glUniform1f(
        glGetUniformLocation(shaderProgram, name.c_str()),
        value
    );
}

void Shader::SetUniformVec3(const std::string& name, glm::vec3 value) const {
    glUniform3fv(
        glGetUniformLocation(shaderProgram, name.c_str()),
        1, glm::value_ptr(value)
    );
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 value) const {
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, name.c_str()), 
        1, GL_FALSE,
        glm::value_ptr(value)
    );
}

void Shader::CheckCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

            std::cerr << "Não foi possível compilar shader (" << type << "):\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);

            std::cerr << "Não foi possível compilar programa shader:\n" << infoLog << std::endl;
        }
    }
}

unsigned int Shader::CompileShader(unsigned int type, const char* src) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    CheckCompileErrors(shader, (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT");

    return shader;
}

std::string Shader::ReadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo shader: " << path << std::endl;

        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}