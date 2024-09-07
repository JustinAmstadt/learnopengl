float rand(int pixel_index, int sample_index) {
    return fract(sin(float(pixel_index + sample_index * 31)) * 43758.5453);
}


float rand_range(int pixel_index, int sample_index, float min, float max) {
    return min + (max - min) * rand(pixel_index, sample_index);
}

vec3 rand_vec3(int pixel_index, int sample_index) {
    return vec3(rand(pixel_index * 431, sample_index * 255), rand(pixel_index * 37, sample_index * 91), rand(pixel_index * 436, sample_index * 380));
}

vec3 rand_vec3_range(int pixel_index, int sample_index, int min, int max) {
    return vec3(rand_range(pixel_index * 431, sample_index * 255, min, max), rand_range(pixel_index * 37, sample_index * 91, min, max), rand_range(pixel_index * 436, sample_index * 380, min, max));
}

vec3 rand_unit_vec3(int pixel_index, int sample_index) {
    while (true) {
        vec3 p = rand_vec3_range(pixel_index, sample_index, -1, 1);
        float lensq = dot(p, p);
        if (1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }

    return vec3(0,0,0);
}

vec3 random_on_hemisphere(int pixel_index, int sample_index, vec3 normal) {
    vec3 on_unit_sphere = rand_unit_vec3(pixel_index, sample_index);
    if (dot(on_unit_sphere, normal) > 0.0) { // In the same hemisphere as normal
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}