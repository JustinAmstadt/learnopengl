bool is_front_face(Ray r, vec3 outward_normal) {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    bool front_face = dot(r.direction, outward_normal) < 0;
    return front_face;
}