#pragma once
#include <memory>
#include "Animation.h"

class Font {

    std::string name;
    const Shader* program;
    std::unique_ptr<Animation> sprite;

    bool isStandard;
    int rows, columns;

    float kerning = 0;
    float lineSpace = 0;

    std::unordered_map<char, int> chars;
    std::unordered_map<std::string,int> tokens;

public:

    Font(std::string  name, const std::string& path, const Shader* program);

    void drawText(std::string text, const Vector2& offset) const;
    void drawText(std::string text, const Vector2& offset, float scale) const;

    int getCharIndex(char c) const;
    void setKerning(float k) {kerning = k;}
    float getKerning() const {return kerning;}
    void setLineSpace(float l) {lineSpace = l;}
    float getLineSpace() const {return lineSpace;}
    void drawChar(char c, const Vector2& offset, float scaleMult) const;
    float getCharacterSize() const {return sprite->getTextureMap().getCellWidth();}

};
