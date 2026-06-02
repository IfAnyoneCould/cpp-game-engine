#include "WorldObject.h"

void WorldObject::drawObjects() const {
    for (const auto& [obj,data] : objects) {
        for (const auto& v : data) {
            obj.getShape().draw(v.first);
        }
    }
}
