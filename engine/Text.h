#pragma once
#include <memory>

#include "Font.h"
#include "Vector2.h"


class Text {
    const Font* font;
    std::string text;
    Vector2 offset;

    float scale;
    float scaleFactor = 1;

public:
    Text(std::string  text, const Font& font, const Vector2& offset);

    void draw() const;

    float getScale() const {return scale;}
    void setScale(float s) {scale = s; scaleFactor = s / font->getCharacterSize();}

    const Vector2& getOffset() const {return offset;}
    void setOffset(const Vector2& o) {offset = o;}

};
