#include "Text.h"

#include <utility>


Text::Text(std::string  text, const Font &font, const Vector2 &offset)
    : font(&font), text(std::move(text)), offset(offset){}

void Text::draw() const {
    Vector2 o = offset;
    for (const auto& c : text) {
        switch(c) {
            case ' ': o.x += font->getCharacterSize() * scaleFactor + font->getKerning(); break;
            case '\n':
                o.y -= font->getCharacterSize() * scaleFactor - font->getLineSpace();
                o.x = offset.x;
                break;
            default:
                font->drawChar(c,o,scaleFactor);
                o.x += font->getCharacterSize() * scaleFactor + font->getKerning();
                break;
        }
    }
}
