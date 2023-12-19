#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>

#include <iostream>

using color = glm::vec3;

void write_color(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.r) << ' '
        << static_cast<int>(255.999 * pixel_color.g) << ' '
        << static_cast<int>(255.999 * pixel_color.b) << '\n';
}

#endif