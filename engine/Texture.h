#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>
#include <glad/glad.h>


class Texture {
    unsigned int id;

    static unsigned int loadTexture(const std::string& path);

public:
    Texture() : id(0) {};
    Texture(Texture&& other) noexcept : id(other.getId()){other.id = 0;};
    Texture(const std::string& path) : id(loadTexture(path)) {};
    ~Texture() {glDeleteTextures(1,&id);}

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) noexcept;

    unsigned int getId() const {return id;}

    void bind() const {glBindTexture(GL_TEXTURE_2D,id);}

};
