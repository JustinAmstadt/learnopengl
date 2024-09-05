// Function to intersect a ray with a sphere
HitReturn hit_sphere(Ray ray, Sphere sphere, float cur_ray_tmax) {
    HitReturn return_val = HitReturn(HitRecord(vec3(0.0, 0.0, 0.0),vec3(0.0, 0.0, 0.0), 0.0, true), true);

    vec3 oc = sphere.center - ray.origin;
    float a = dot(ray.direction, ray.direction); // This is length squared
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float h = dot(ray.direction, oc);
    float discriminant = h * h - a * c;

    if (discriminant < 0.0) {
        return_val.hit = false;
        return return_val;
    }
    float sqrtd = sqrt(discriminant);
    float root = (h - sqrtd) / a;
    if (root <= ray_tmin || cur_ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || cur_ray_tmax <= root) {
            return_val.hit = false;
            return return_val;
        }
    }

    return_val.rec.t = root;
    return_val.rec.p = rayAt(ray, return_val.rec.t);
    return_val.rec.normal = (return_val.rec.p - sphere.center) / sphere.radius;

    if(is_front_face(ray, return_val.rec.normal)) {
        return_val.rec.front_face = true;
    } else {
        return_val.rec.front_face = false;
        return_val.rec.normal = -return_val.rec.normal;
    }

    return_val.hit = true;
    return return_val;
}