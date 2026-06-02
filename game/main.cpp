#include "../engine/Game.h"

unsigned int program;
RegularPolygon* shape;
PlatformerController* controller;
GameObject* a;

Rectangle* rect;
GameObject* b;

Camera* cam;

const Uint8* keys;

void start() {
    keys = Engine::getKeys();
    program = Engine::getProgram();

    shape = new RegularPolygon(50.0f,6,program);
    controller = new PlatformerController(500.0f,500.0f,keys);
    a = new GameObject(shape, 10);
    a->setKinematic(true);
    a->setPosition(Vectors::WORLD_CENTER);
    a->addController(controller);

    rect = new Rectangle(Constants::WORLD_WIDTH,100,program);
    b = new GameObject(rect);

}

void update(double deltaTime) {

    Collision col = Physics::collision(*a,*b);
    a->updateControllers(deltaTime);
    Physics::collision(*a,*b,col);
    a->applyVelocity(deltaTime);

}

void render() {

    rect->drawWireFrame();
    a->getShape().drawWireFrame();
}


int main(int arc, char* argv[]) {\
    Engine::init();\
    start();
    constexpr double PHYSICS_STEP = 1.0 / 240.0; \
    double accumulator = 0; \
    while(Engine::isRunning()) { \
        Engine::startFrame(); \
        accumulator += Engine::getDeltaTime(); \
        while (accumulator >= PHYSICS_STEP) { \
            update(PHYSICS_STEP); \
            accumulator -= PHYSICS_STEP; \
        } \
        render(); \
        Engine::endFrame(); \
    }   \
    Engine::quit(); \
    return 0; \
}




//RUN