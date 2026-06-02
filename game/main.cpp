#include "../engine/Game.h"

unsigned int program;
RegularPolygon* shape;
MovementController* controller;
GameObject* a;

Rectangle* rect;
GameObject* b;

Camera* cam;

const Uint8* keys;

void start() {
    keys = Engine::getKeys();
    program = Engine::getProgram();

    shape = new RegularPolygon(100.0f,6,program);
    controller = new MovementController(500.0f,keys);
    a = new GameObject(shape, 10);
    a->setKinematic(true);
    a->setPosition(Vectors::WORLD_CENTER);
    a->addController(controller);

    rect = new Rectangle(Constants::WORLD_WIDTH,100,program);
    b = new GameObject(rect);

}

void update(double deltaTime) {

    Physics::collision(*a,*b);

    a->applyVelocity(deltaTime);

    a->getShape().drawNormals();

    rect->drawWireFrame();
    a->getShape().drawWireFrame();

}


int main(int arc, char* argv[]) {
    Engine::init();
    start();
    while(Engine::isRunning()) {
        Engine::startFrame();
        update(Engine::getDeltaTime());
        Engine::endFrame();
    }
    Engine::quit();
    return 0;
}



//RUN