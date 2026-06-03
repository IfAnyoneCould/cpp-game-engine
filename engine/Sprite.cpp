#include "Sprite.h"
#include "Mat4.h"
#include <iostream>

void Sprite::setSize(float w, float h) {
    this->width = w;
    this->height = h;
}

void Sprite::init() {
    program->use();

    addUniform("uvSize");
    addUniform("uvOffset");
    addUniform("model");
    addUniform("useTexture");
    addUniform("tex");

    setSize(width,height);

    glUniform2f(locations.at("uvSize"), map->getCellWidth(), map->getCellHeight());
    Vector2 uvOffset = map->getOffset(index);
    glUniform2f(locations.at("uvOffset"),uvOffset.x,uvOffset.y);

    std::vector vec1(vertices.begin(),vertices.end());
    std::vector vec2(indices.begin(),indices.end());

    buffer = Vertex::getBufferObjects(vec1,vec2);
}



Sprite::Sprite(const Texture &t, const Shader &s)
    : uniqueMap(TextureMap(t)), map(&uniqueMap), program(&s), width(t.getWidth()), height(t.getHeight()), index(0){
    init();
}

Sprite::Sprite(const Texture &t, float width, float height, const Shader &s)
    : uniqueMap(TextureMap(t)), map(&uniqueMap), program(&s), width(width), height(height), index(0){
    init();
}

Sprite::Sprite(const TextureMap &t, int index, const Shader &s)
    : map(&t), program(&s), width(t.getTexture()->getWidth() / t.getColumns()), height(t.getTexture()->getHeight() / t.getRows()), index(index){
    init();
}

Sprite::Sprite(const TextureMap &t, int index, float width, float height, const Shader &s)
    : map(&t), program(&s), width(width), height(height), index(index) {
    init();
}

void Sprite::addUniform(std::string name) {
    locations.emplace(name,glGetUniformLocation(program->getId(),name.c_str()));
}

void Sprite::draw() const {
    glActiveTexture(GL_TEXTURE0);
    map->getTexture()->bind();
    program->use();

    glUniform1i(locations.at("useTexture"),1);
    Mat4 model = Mat4::translate(offset) * Mat4::scale({width,height});
    glUniformMatrix4fv(locations.at("model"),1,GL_FALSE,model.getM());
    glUniform1i(locations.at("tex"),0);

    glBindVertexArray(buffer.VAO);
    glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,0);
}

void Sprite::setIndex(int i) {
    index = i;
    Vector2 uvOffset = map->getOffset(index);
    glUniform2f(locations.at("uvOffset"),uvOffset.x,uvOffset.y);
}
