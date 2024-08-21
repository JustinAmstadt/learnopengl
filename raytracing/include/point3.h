#ifndef POINT3_H
#define POINT3_H

#include <glm/glm.hpp>

namespace rtracer {

    class point3 : glm::vec4 {
    public:

        point3(glm::vec3 pos) {
            this->x = pos.x;
            this->y = pos.y;
            this->z = pos.z;
            this->w = 1.0f;
        }

    };

}

#endif