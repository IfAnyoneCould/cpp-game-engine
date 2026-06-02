#include "../engine/Game.h"

unsigned int program;
RegularPolygon* shape;
MovementController* controller;
GameObject* a;

Rectangle* rect;
GameObject* b;

const Uint8* keys;

void start() {

    keys = Engine::getKeys();


    program = Shader::getProgram({
        {"shaders/vertex.glsl",GL_VERTEX_SHADER},
        {"shaders/fragment.glsl",GL_FRAGMENT_SHADER}});

    shape = new RegularPolygon(200.0f,6,program);
    controller = new MovementController(500.0f);
    a = new GameObject(shape, 10);
    a->setKinematic(true);

    rect = new Rectangle(100,100,program);
    b = new GameObject(rect);


}

void update(double deltaTime) {

    controller->update(keys);

    a->setVelocity(controller->getVelocity());

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