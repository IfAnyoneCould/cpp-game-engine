#include "Sprite.h"
#include "Mat4.h"

Sprite::Sprite(const Texture &t, const Shader &s)
    : uniqueMap(TextureMap(t)), map(&uniqueMap), program(&s), width(t.getWidth()), height(t.getHeight()), index(1){

    vertices[0] = {0,0};
    vertices[1] = {width,0};
    vertices[2] = {0,height};
    vertices[3] = {width,height} ;

    uvVertices = map->getVertices(index);

    std::vector<Vector2> vec1(vertices.begin(), vertices.end());
    std::vector<Vector2> vec2(uvVertices.begin(),uvVertices.end());

    buffer = Vertex::getBufferObjects(vec1,vec2);

    addUniform("model");
    addUniform("useTexture");
    addUniform("tex");
}

Sprite::Sprite(const TextureMap &t, int index, const Shader &s)
    : map(&t), program(&s), width(t.getTexture()->getWidth() / t.getColumns()), height(t.getTexture()->getHeight() / t.getRows()), index(index){
    vertices[0] = {0,0};
    vertices[1] = {width,0};
    vertices[2] = {0,height};
    vertices[3] = {width,height} ;

    uvVertices = map->getVertices(index);

    std::vector<Vector2> vec1(vertices.begin(), vertices.end());
    std::vector<Vector2> vec2(uvVertices.begin(),uvVertices.end());
    std::vector<unsigned int> vec3(indices.begin(),indices.end());

    buffer = Vertex::getBufferObjects(vec1,vec2,vec3);

    addUniform("model");
    addUniform("useTexture");
    addUniform("tex");

}

void Sprite::addUniform(std::string name) {
    locations.emplace(name,glGetUniformLocation(program->getId(),name.c_str()));
}

void Sprite::draw() const {
    glActiveTexture(GL_TEXTURE0);
    map->getTexture()->bind();
    program->use();

    glUniform1i(locations.at("useTexture"),1);
    Mat4 model = Mat4::translate(offset);
    glUniformMatrix4fv(locations.at("model"),1,GL_FALSE,model.getM());
    glUniform1i(locations.at("tex"),0);

    glBindVertexArray(buffer.VAO);
    glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,0);
}
