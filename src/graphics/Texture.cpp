#include "graphics/Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>

Texture::Texture(const std::string& path) {
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(
        path.c_str(),
        &width, &height,
        &nrChannels,
        0
    );

    if (data) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            format, 
            width, height, 
            0, 
            format, 
            GL_UNSIGNED_BYTE, 
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        std::cerr << "Não foi possível carregar a textura: " << path << std::endl;
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Texture::Bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}