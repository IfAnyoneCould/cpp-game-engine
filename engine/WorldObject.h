#pragma once
#include <deque>
#include "GameObject.h"


class WorldObject {

    std::unordered_map<std::string,GameObject> objects;
    std::unordered_map<std::string,std::vector<Vector2>> positions;
    std::unordered_map<std::string,Texture> textures;
    std::unordered_map<unsigned int,std::string> colorPairs;
    std::deque<Animation> animations;
    std::deque<std::unique_ptr<Shape>> shapes;

    static std::string parseKey(const std::string& line);
    static std::string parseVal(const std::string& line);
    static std::vector<std::string> parseComma(const std::string& line);

    void loadImage(std::string path, float worldWidth, float worldHeight);

public:
    WorldObject(const std::string& path, const Shader& program);

    void drawObjects(double deltaTime) const;
    std::vector<Collision> getCollisions(GameObject* other);
    void resolveCollisions(GameObject* other, const std::vector<Collision>& cols);
};
