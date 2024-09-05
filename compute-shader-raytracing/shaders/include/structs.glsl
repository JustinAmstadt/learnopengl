struct Sphere {
    vec3 center;
    float radius;
    vec3 color;
};

struct Ray {
    vec3 origin;
    vec3 direction;
};

struct HitRecord {
    vec3 p;
    vec3 normal;
    float t;
    bool front_face;
    bool hit; // This is a temp value so that I can return this and tell whether or not there was a hit that time
};
