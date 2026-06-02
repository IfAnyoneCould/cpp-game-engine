#include "Texture.h"

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

    unsigned char* data = stbi_load(path.c_str(),&width,&height,&channels,0);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;

}
