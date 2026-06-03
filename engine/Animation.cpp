#include "Animation.h"

Animation::Animation()
    : program(), map(), first(-1), last(-1), current(-1), timeStep(0.0f) {}

Animation::Animation(const TextureMap &t, int first, int last, float timeStep, const Shader& shader)
    : program(&shader), map(&t), first(first), last(last), current(first), timeStep(timeStep){
    sprite = new Sprite(*map,first,*program);
}

void Animation::draw(double deltaTime) {
    sprite->setIndex(current);
    sprite->setOffset(offset);
    sprite->draw();

    currentTime+=deltaTime;
    if (currentTime >= timeStep) {
        if (current >= last) current = first;
        else current++;
        currentTime = 0;
    }

}

Animation::Animation(Animation && other) noexcept
    : program(other.program), map(other.map), sprite(other.sprite),
    first(other.first), last(other.last), current(other.current),
    timeStep(other.timeStep), currentTime(other.currentTime), offset(other.offset){
    other.sprite = nullptr;
    other.program = nullptr;
    other.map = nullptr;
}

Animation &Animation::operator=(Animation && other) noexcept {
    if (this != &other) {
        delete sprite;
        sprite = other.sprite;
        map = other.map;
        program = other.program;
        first = other.first;
        last = other.last;
        current = other.current;
        timeStep = other.timeStep;
        currentTime = other.currentTime;
        offset = other.offset;
        other.sprite = nullptr;
        other.map = nullptr;
        other.program = nullptr;
    }
    return *this;
}
