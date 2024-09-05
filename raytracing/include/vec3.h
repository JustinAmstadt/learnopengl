#ifndef VEC3_H
#define VEC3_H

#include <glm/glm.hpp>

namespace rtracer {

    class vec3 : glm::vec4 {

        vec3(glm::vec3 pos) {
            this->x = pos.x;
            this->y = pos.y;
            this->z = pos.z;
            this->w = 0.0f;
        }
    };

}

#endif