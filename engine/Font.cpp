#include "Font.h"
#include "Text.h"
#include <utility>

Font::Font(std::string  name, const std::string& path, const Shader *program) : name(std::move(name)), program(program), isStandard(true), rows(10), columns(10){

    Texture t(path);
    TextureMap m(t,rows,columns);
    sprite = std::make_unique<Animation>(Animation(m,t.getWidth(),t.getHeight(),0,*program));
}

int Font::getCharIndex(char c) const {
    if (isStandard) return c - 32;
    return chars.at(c);
}

void Font::drawChar(char c, const Vector2& offset, float scaleMult) const {
    sprite->setCurrentFrame(getCharIndex(c));
    sprite->setOffset(offset);
    sprite->setScale(scaleMult,scaleMult);
    sprite->draw(0);
}

void Font::drawText(std::string text, const Vector2 &offset) const {
    Text temp(std::move(text), *this, offset);
    temp.draw();
}

void Font::drawText(std::string text, const Vector2 &offset, float scale) const {
    Text temp(std::move(text), *this, offset);
    temp.setScale(scale);
    temp.draw();
}
