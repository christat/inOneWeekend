#ifndef UTILSH
#define UTILSH

#include<math.h>
#include "vec3.h"

Vec3 random_from_tangent_unit_sphere() {
    Vec3 random;
    do {
        random = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1.0, 1.0, 1.0);
    } while (random.length_squared() >= 1.0);
    return random;
}

Vec3 random_in_unit_disk() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(), 0) - Vec3(1, 1, 0);
    } while (Vec3::dot(p, p) >= 1.0);
    return p;
}

Vec3 reflect(const Vec3& vector, const Vec3& normal) {
    return vector - 2 * Vec3::dot(vector, normal) * normal;
}

bool refract(const Vec3& vector, const Vec3& normal, float ni_over_nt, Vec3& refracted) {
    Vec3 normalized = Vec3::normalized(vector);
    float dt = Vec3::dot(normalized, normal);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
    if (discriminant > 0.0) {
        refracted = ni_over_nt * (normalized - normal * dt) - normal * sqrt(discriminant);
        return true;
    }
    return false;
}

#endif