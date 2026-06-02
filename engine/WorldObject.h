#pragma once
#include "GameObject.h"


class WorldObject {

    std::unordered_map<GameObject,std::vector<std::pair<Vector2,int>>> objects;

public:
    void drawObjects() const;
    void updateObjects();
    void collisions(GameObject* obj);

    void addObject(GameObject obj);
    void removeObject(GameObject obj);

};
