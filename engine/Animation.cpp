#include "Animation.h"

Animation::Animation()
    : program(), first(-1), last(-1), current(-1), timeStep(0.0f), isSprite(false) {}

Animation::Animation(const TextureMap &t,float width, float height, int first, int last, float timeStep, const Shader& shader)
    : program(&shader), first(first), last(last), current(first), timeStep(timeStep), isSprite(false){
    sprite = new Sprite(t,first,*program);
    setSize(width,height);
}

Animation::Animation(const TextureMap &t, float width, float height, int index, const Shader &shader)
    : program(&shader), first(index), last(index), current(index), timeStep(0.0f), isSprite(true) {
    sprite = new Sprite(t,index,shader);
    setSize(width,height);
}

Animation::Animation(const Texture &t, float width, float height, const Shader &shader)
    : program(&shader), first(0), last(0), current(0), timeStep(0.0f), isSprite(true){
    sprite = new Sprite(t,*program);
    setSize(width,height);
}

Animation::Animation(const Texture &t, float width, float height, int index, const Shader &shader)
    : program(&shader), first(index), last(index), current(index), timeStep(0.0f), isSprite(true){
    sprite = new Sprite(t,index,*program);
    setSize(width,height);
}

Animation::Animation(const Texture &t, float width, float height, int first, int last, float timeStep, const Shader &s)
    : program(&s), first(first), last(last), current(first), timeStep(timeStep), isSprite(false){
    sprite = new Sprite(t,*program);
    setSize(width,height);
}

void Animation::draw(double deltaTime) {
    if (!isSprite) sprite->setIndex(current);

    sprite->setOffset(offset);
    sprite->draw();

    if (!isSprite) {
        currentTime+=deltaTime;
        if (currentTime >= timeStep) {
            if (current >= last) current = first;
            else current++;
            currentTime = 0;
        }
    }
}

Animation::Animation(Animation && other) noexcept
    : program(other.program), sprite(other.sprite),
    first(other.first), last(other.last), current(other.current), isSprite(other.isSprite),
    timeStep(other.timeStep), currentTime(other.currentTime), offset(other.offset){
    other.sprite = nullptr;
    other.program = nullptr;
}

Animation &Animation::operator=(Animation && other) noexcept {
    if (this != &other) {
        delete sprite;
        sprite = other.sprite;
        program = other.program;
        first = other.first;
        last = other.last;
        current = other.current;
        timeStep = other.timeStep;
        currentTime = other.currentTime;
        offset = other.offset;
        isSprite = other.isSprite;
        other.sprite = nullptr;
        other.program = nullptr;
    }
    return *this;
}
