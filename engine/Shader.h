#pragma once
#include <string>
#include <glad/glad.h>
#include "vector"

class Shader {
    unsigned int id;

    std::string loadShader(std::string path);
    unsigned int getShader(const std::string &path, GLenum type);
    unsigned int getProgram(std::initializer_list<std::pair<std::string,GLenum>> data);
    unsigned int getProgram(const std::vector<unsigned int>& data);
public:

    Shader() : id(0) {};
    Shader(Shader&& other)  noexcept : id(other.id) {};
    Shader(std::initializer_list<std::pair<std::string,GLenum>> data) : id(getProgram(data)){};
    Shader(const std::vector<unsigned int>& data) : id(getProgram(data)){}
    ~Shader() {glDeleteProgram(id);}

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) noexcept;

    unsigned int getId() const {return id;}
    void use() const {glUseProgram(id);}

};