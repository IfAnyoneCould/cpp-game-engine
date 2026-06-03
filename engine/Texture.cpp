#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include <stb_image.h>
#include <iostream>

Texture &Texture::operator=(Texture && other) noexcept {
    if (id != other.getId()) {
        glDeleteTextures(1,&id);
        id = other.id;
        other.id = 0;
    }
    return *this;
}

unsigned int Texture::loadTexture(const std::string &path) {
    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(),&width,&height,&channels,4);

    if (!data) {
        std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
    }

    this->w = width;
    this->h = height;

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    stbi_image_free(data);

    return texture;

}
