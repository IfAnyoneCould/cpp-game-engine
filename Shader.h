#pragma once
#include <string>
#include <glad/glad.h>
#include "vector"

class Shader {
public:
    static std::string loadShader(std::string path);
    static unsigned int getShader(const std::string &path, GLenum type);
    static unsigned int getProgram(std::initializer_list<std::pair<std::string,GLenum>> data);
    static unsigned int getProgram(const std::vector<unsigned int>& data);
};