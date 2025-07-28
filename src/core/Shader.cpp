#include "core/Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  // clangd tava reclamando que tem que criar uns objetos separados :(
  // Neovim btw
  std::string vertexCode = ReadFile(vertexPath);
  std::string fragmentCode = ReadFile(fragmentPath);

  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  CheckCompileErrors(vertexShader, "VERTEX");

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  CheckCompileErrors(fragmentShader, "FRAGMENT");

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  CheckCompileErrors(ID, "PROGRAM");

  // Já está linkado no ID
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(ID); }

void Shader::Bind() const { glUseProgram(ID); }

void Shader::Unbind() const { glUseProgram(0); }

int Shader::GetUniformLocation(const std::string &name, bool suppress) const {
  int loc = glGetUniformLocation(ID, name.c_str());

  if (loc == -1 && !suppress) {
    std::cerr << "Erro ao pegar uniform: '" << name << "'!\n";
  }

  return loc;
}

void Shader::SetInt(const std::string &name, int value) const {
  glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::SetMatrix4(const std::string &name, const glm::mat4 &value) const {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE,
                     glm::value_ptr(value));
}

// "Ain, é melhor ler arquivo com python..."
// VAI SE FUDER!!!! ENFIA A COBRA NO RABO!
std::string Shader::ReadFile(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Não foi possível abrir o shader em: " << path << "\n";

    return "";
  }

  // PRA QUE? PRA QUE FAZER UM "STREAM"??? É YOUTUBER POR A CASO???
  // PORQUE NN TEM UMA FUNÇÃO PARA LER ARQUIVO NO C++??????
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

// Não sei o que djabo é isso, só sei que verifica por erro :D
void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
  int success;
  char infolog[1024]; // Lá ele

  if (type == "PROGRAM") {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infolog);

      std::cerr << "Erro na linkagem dos shaders! Log:\n" << infolog << "\n";
    }
  } else {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infolog);

      std::cerr << "Erro no " << type << " shader! Log:\n" << infolog << "\n";
    }
  }
}
