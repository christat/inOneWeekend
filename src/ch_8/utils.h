#ifndef UTILSH
#define UTILSH

#include "vec3.h"

Vec3 random_from_tangent_unit_sphere() {
    Vec3 random;
    do {
        random = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1.0, 1.0, 1.0);
    } while (random.length_squared() >= 1.0);
    return random;
}

Vec3 reflect(const Vec3& vector, const Vec3& normal) {
    return vector - 2 * Vec3::dot(vector, normal) * normal;
}

#endif