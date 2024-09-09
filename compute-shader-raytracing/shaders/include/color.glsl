vec3 linear_to_gamma(vec3 color) {
    if (color.r > 0) {
        color.r = sqrt(color.r);
    }

    if (color.g > 0) {
        color.g = sqrt(color.g);
    }
    
    if (color.b > 0) {
        color.b = sqrt(color.b);
    }

    return color;
}