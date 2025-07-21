#pragma once

class Texture {
public:
  Texture(const char *path);
  ~Texture();

  void Bind(int unit = 0) const;
  void Unbind() const;

private:
  unsigned int ID;
};
