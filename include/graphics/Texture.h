#pragma once

#include <string>

class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int unit=0) const;
    void Unbind() const;

    unsigned int GetID() const { return ID; }
private:
    unsigned int ID;
    int width, height, nrChannels;
};