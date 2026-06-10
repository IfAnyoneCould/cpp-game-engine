#include "../engine/Game.h"

Rectangle* shape;
PlatformerController* controller;
GameObject* a;

WorldObject* world;

Camera* cam;

Texture* tex;
TextureMap* map;
Animation* sprite;

const Uint8* keys;

void start() {
    keys = Engine::getKeys();


    shape = new Rectangle(98.0f,98.0f,Engine::getProgram());
    controller = new PlatformerController(500.0f,500.0f,keys);
    a = new GameObject(shape, 10,"hi");
    a->setKinematic(true);
    a->setPosition(Vectors::WORLD_CENTER);
    a->addController(controller);

    world = new WorldObject("worlds/world.world",Engine::getProgram());
    tex = new Texture("textures/test.png");
    //map = new TextureMap(*tex,2,2);
    sprite = new Animation(*tex,100,100,Engine::getProgram());
    sprite->setOffset(Vectors::WORLD_CENTER);

}

void update(double deltaTime) {
    a->getBody().setOnGround(false);
    std::vector<Collision> cols = world->getCollisions(a);
    a->updateControllers(deltaTime);
    world->resolveCollisions(a,cols);
    a->applyVelocity(deltaTime);
    sprite->setOffset(a->getPosition());

}

void render(double deltaTime) {
    world->drawObjectsWireFrame();
    world->drawObjects(deltaTime);
    a->getShape().drawWireFrame();
    sprite->draw(deltaTime);
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
        render(Engine::getDeltaTime()); \
        Engine::endFrame(); \
    }   \
    Engine::quit(); \
    return 0; \
}




//RUN