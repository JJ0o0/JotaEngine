#pragma once

#include <glm/glm.hpp>
#include <string>

class Shader {
public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  unsigned int GetID() const { return ID; }

  int GetUniformLocation(const std::string &name, bool suppress = false) const;

  void SetInt(const std::string &name, int value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetVec3(const std::string &name, const glm::vec3 &value) const;
  void SetMatrix4(const std::string &name, const glm::mat4 &value) const;

private:
  unsigned int ID;

  void CheckCompileErrors(unsigned int shader, std::string type);

  std::string ReadFile(const std::string &path);
};
