// Function to intersect a ray with a sphere
HitRecord hit_sphere(Ray ray, Sphere sphere, float cur_ray_tmax, HitRecord rec) {
    vec3 oc = sphere.center - ray.origin;
    float a = dot(ray.direction, ray.direction); // This is length squared
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float h = dot(ray.direction, oc);
    float discriminant = h * h - a * c;

    if (discriminant < 0.0) {
        rec.hit = false;
        return rec;
    }
    float sqrtd = sqrt(discriminant);
    float root = (h - sqrtd) / a;
    if (root <= ray_tmin || cur_ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || cur_ray_tmax <= root) {
            rec.hit = false;
            return rec;
        }
    }

    rec.t = root;
    rec.p = rayAt(ray, rec.t);
    rec.normal = (rec.p - sphere.center) / sphere.radius;

    if(is_front_face(ray, rec.normal)) {
        rec.front_face = true;
    } else {
        rec.front_face = false;
        rec.normal = -rec.normal;
    }

    rec.hit = true;
    return rec;
}