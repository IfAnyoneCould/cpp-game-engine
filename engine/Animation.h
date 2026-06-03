#pragma once
#include "Sprite.h"

class Animation {
    const Shader* program;
    const TextureMap* map;
    Sprite* sprite = nullptr;
    int first, last, current;
    float timeStep, currentTime = 0;
    Vector2 offset;

public:
    Animation();
    Animation(const TextureMap& t,float width,float height, int first, int last, float timeStep,const Shader& shader);
    ~Animation() {delete sprite;}

    Animation(Animation&) = delete;
    Animation(Animation&&) noexcept;
    Animation& operator=(Animation&) = delete;
    Animation& operator=(Animation&&) noexcept;

    void draw(double deltaTime);

    //get and set
    void setOffset(const Vector2& v) {offset = v;}
    void addOffset(const Vector2& v) {offset += v;}
    void setSize(float width, float height) const {sprite->setSize(width,height);}
    const Vector2& getOffset() const {return offset;}


};