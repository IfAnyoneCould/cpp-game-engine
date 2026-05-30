#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string Shader::loadShader(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Failed to open shader: " << path << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::getShader(const std::string &path, const GLenum type) {
    const std::string str = loadShader(path);
    const char* source = str.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader,1,&source,NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED (" << type << ")\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}

unsigned int Shader::getProgram(std::initializer_list<std::pair<std::string, GLenum> > data) {
    unsigned int program = glCreateProgram();
    for (const auto& pair : data) {
        unsigned int shader = getShader(pair.first,pair.second);
        glAttachShader(program,shader);
        glDeleteShader(shader);
    }
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return program;
}

unsigned int Shader::getProgram(const std::vector<unsigned int>& data) {
    unsigned int program = glCreateProgram();
    for (const auto& shader : data) {
        glAttachShader(program,shader);
    }
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return program;
}
