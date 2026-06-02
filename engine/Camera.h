#pragma once
#include "Vector2.h"
#include "Mat4.h"
#include <glad/glad.h>

class Camera {

    unsigned int program;
    unsigned int loc;
    float scale;
    Vector2 pos;

public:

    explicit Camera(unsigned int program) : program(program), loc(glGetUniformLocation(program,"view")), scale(1.0f), pos({}) {};

    void setPosition(const Vector2& position) {this->pos = position;update();}
    void addPosition(const Vector2& position) {this->pos+= position;update();}
    void setScale(float scale) {this->scale = scale;}
    void update() const {
        Mat4 view = Mat4::translate(-pos) * Mat4::scale({scale,scale});
        glUniformMatrix4fv(loc,1,GL_FALSE,view.getM());
    }

    Vector2 getPosition() const {return pos;}
    float getScale() const {return scale;}


};