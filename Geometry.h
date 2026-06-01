#pragma once
#include "Vector2.h"
#include "Vertex.h"

namespace Geometry {
    inline bool linesIntersect(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d) {
        float oa = Vector2::orient(c,d,a),
         ob = Vector2::orient(c,d,b),
         oc = Vector2::orient(a,b,c),
         od = Vector2::orient(a,b,d);

        return (oa*ob < 0 && oc*od < 0);
    }

    inline float getOverlap(float a1, float a2, float b1, float b2) {
        return std::min(a2, b2) - std::max(a1, b1);
    }

    inline std::vector<Vector2> removeParallelVectors(const std::vector<Vector2>& list) {

        std::vector<Vector2> result;

        for (const auto& a : list) {
            bool parallel = false;
            for (const auto& b : result) {
                float d = std::abs(Vector2::dot(a,b));
                if (d > 0.999) {
                    parallel = true;
                    break;
                }
            }
            if (!parallel) result.push_back(a);
        }
        return result;
    }

    inline void drawLine(const Vector2& a, const Vector2& b, unsigned int program) {

        BufferObject buffer = Vertex::getBufferObjects({a,b});

        glUseProgram(program);
        glBindVertexArray(buffer.VAO);
        glDrawArrays(GL_LINES,0,2);

    }

}