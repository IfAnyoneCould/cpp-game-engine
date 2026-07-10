#pragma once
#include "Sprite.h"

class Animation {
protected:
    const Shader* program;
    Sprite* sprite = nullptr;
    int first, last;

private:
    int current;
    float timeStep, currentTime = 0;
    bool isSprite;

public:
    Animation();
    Animation(const TextureMap& t,float width,float height, int first, int last, float timeStep,const Shader& shader);
    Animation(const TextureMap& t, float width, float height, int index, const Shader& shader);
    Animation(const Texture& t, float width, float height, int first, int last, float timeStep, const Shader& s);
    Animation(const Texture& t, float width, float height, int index, const Shader& shader);
    Animation(const Texture& t, float width, float height, const Shader& shader);
    ~Animation() {delete sprite;}

    Animation(Animation&) = delete;
    Animation(Animation&&) noexcept;
    Animation& operator=(Animation&) = delete;
    Animation& operator=(Animation&&) noexcept;

    void draw(double deltaTime);

    //get and set
    void setOffset(const Vector2& v) const {if (sprite) sprite->setOffset(v);}
    void addOffset(const Vector2& v) const {sprite->setOffset(sprite->getOffset() + v);}
    void setSize(float width, float height) const {sprite->setSize(width,height);}
    void setScale(float xScale, float yScale) const {sprite->setScale(xScale,yScale);}
    void setCurrentFrame(int frame) { if (frame >= first && frame <= last) {current = frame;}}
    int getCurrentFrame() const {return current;}
    const Vector2& getOffset() const {return sprite->getOffset();}
    const TextureMap& getTextureMap() const {return sprite->getMap();}
    const Sprite& getSprite() const {return *sprite;}


};