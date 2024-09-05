vec3 rayAt(Ray r, float t) {
    return r.origin + t * r.direction;
}