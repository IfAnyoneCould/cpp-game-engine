#include "WorldObject.h"
#include <fstream>
#include <iostream>
#include <optional>
#include "Physics.h"
#include <sstream>
#include <stb_image.h>
#include "Rectangle.h"
#include "RegularPolygon.h"

void WorldObject::drawObjects(double deltaTime) const {
    for (auto& [id, obj] : objects) {
        for (auto& pos : positions.at(id)) {
            obj.setPosition(pos);
            obj.draw(deltaTime);
        }
    }
}
void WorldObject::drawObjectsWireFrame() const {
    for (auto& [id, obj] : objects) {
        for (auto& pos : positions.at(id)) {
            obj.setPosition(pos);
            obj.getShape().drawWireFrame();
        }
    }
}

std::vector<Collision> WorldObject::getCollisions(GameObject *other) {
    std::vector<Collision> cols;
    for (auto& [id, obj] : objects) {
        for (auto& pos : positions.at(id)) {
            obj.setPosition(pos);
            cols.push_back(Physics::collisionAABB(*other,obj));
        }
    }
    return cols;
}

void WorldObject::resolveCollisions(GameObject *other, const std::vector<Collision> &cols) {
    int i = 0;
    for (auto& [id, obj] : objects) {
        for (auto& pos : positions.at(id)) {
            obj.setPosition(pos);
            Physics::collision(*other, obj, cols[i++]);
        }
    }
}

std::string WorldObject::parseKey(const std::string &line) {
    return line.substr(0,line.find('('));
}

std::string WorldObject::parseVal(const std::string &line) {
    int start = line.find('(') + 1;
    int end = line.find(')');
    return line.substr(start,end - start);
}

std::vector<std::string> WorldObject::parseComma(const std::string &line) {
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss,token,',')) {
        tokens.push_back(token);
    }
    return tokens;
}

void WorldObject::loadImage(std::string path, float worldWidth, float worldHeight) {
    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(),&width,&height,&channels,4);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            unsigned char* pixel = data + (y * width + x) * 4;
            unsigned int color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

            if (colorPairs.contains(color)) {
                positions[colorPairs.at(color)].push_back({x * (worldWidth / width), y * (worldHeight / height)});
            }
        }
    }
    stbi_image_free(data);
}

WorldObject::WorldObject(const std::string& path, const Shader& program) {
    std::ifstream header(path);
    if (!header.is_open()) {
        std::cout << "ERROR: could not open worlds file header" << std::endl;
        return;
    }

    float worldWidth = -1, worldHeight = -1;

    std::string line;
    std::optional<std::string> imagePath;
    while (std::getline(header,line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> parsed;
        std::unordered_map<std::string,std::string> keyPairs;
        while (std::getline(ss,token,'#')) {
            if (!token.empty()) parsed.push_back(token);
        }
        for (auto& s : parsed) {
            keyPairs[parseKey(s)] = parseVal(s);
        }
        std::optional<Animation> anim;
        std::unique_ptr<Shape> shape;
        std::optional<std::string> id;
        if (keyPairs.contains("object")) {
            id = keyPairs.at("object");
        }
        if (keyPairs.contains("hbox")) {
            auto vals = parseComma(keyPairs.at("hbox"));
            if (vals[0] == "rect") {
                if (vals.size() == 3) shape = std::make_unique<Rectangle>(std::stof(vals[1]),std::stof(vals[2]),program);
                else std::cout << "Error: malformed " << vals[0] << " hbox, expected 3 args, got " << vals.size() << "\n";
            } else if (vals[0] == "regular") {
                if (vals.size() == 3) shape = std::make_unique<RegularPolygon>(std::stof(vals[1]),std::stoi(vals[2]),program);
                else std::cout << "Error: malformed " << vals[0] << " hbox, expected 3 args, got " << vals.size() << "\n";
            }
        }
        if (keyPairs.contains("animation")) {
            auto vals = parseComma(keyPairs.at("animation"));
            textures.try_emplace(vals[1],Texture(vals[1]));
            if (vals[0] == "single") {
                if (vals.size() == 4) anim.emplace(textures[vals[1]],std::stof(vals[2]),std::stof(vals[3]),program);
                else std::cout << "Error: malformed " << vals[0] << " animation, expected 4 args got " << vals.size() << "\n";
            } else if (vals[0] == "animation") {
                if (vals.size() == 7) {
                    anim.emplace(textures[vals[1]],std::stof(vals[2]),std::stof(vals[3]),
                        std::stoi(vals[4]),std::stoi(vals[5]),std::stof(vals[6]),program);
                } else {
                    std::cout << "Error: malformed " << vals[0] << " animation, expected 7 args got " << vals.size() << "\n";
                }
            } else if (vals[0] == "index") {
                if (vals.size() == 5) anim.emplace(textures[vals[1]],std::stof(vals[2]),std::stof(vals[3]),std::stoi(vals[4]),program);
                else std::cout << "Error: malformed " << vals[0] << " animation, expected 5 args got " << vals.size() << "\n";
            }
        }
        if (keyPairs.contains("color")) {
            auto vals = parseComma(keyPairs.at("color"));
            if (vals.size() == 2) colorPairs.try_emplace(std::stoul(vals[0],nullptr,16),vals[1]);
            else std::cout << "Error: malformed color, expected 2 args got " << vals.size() << "\n";
        }

        if (keyPairs.contains("image")) {
            imagePath = keyPairs.at("image");
        }

        if (keyPairs.contains("world")) {
            auto vals = parseComma(keyPairs.at("world"));
            if (vals.size() == 2) {
                worldWidth = std::stof(vals[0]);
                worldHeight = std::stof(vals[1]);
            }
        }

        if (id.has_value()) {
            if (anim.has_value()) {
                std::optional<GameObject> obj;
                animations.push_back(std::move(*anim));
                Animation* animPtr = &animations.back();
                if (!shape) obj.emplace(animPtr,id.value());
                else {
                    shapes.push_back(std::move(shape));
                    Shape* shapePtr = shapes.back().get();
                    obj.emplace(animPtr,shapePtr,id.value());
                }
                if (obj.has_value()) {
                    objects.try_emplace(id.value(),std::move(obj.value()));
                }
            }
        }
    }

    if (imagePath.has_value()) {
        if (worldWidth == -1 || worldHeight == -1) {
            std::cout << "Error: #world not set\n";
        }
        else loadImage(imagePath.value(),worldWidth,worldHeight);
    }
    else std::cout << "Error: expected '#image' tag but none found\n";
}
