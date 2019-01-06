#ifndef SPHEREH
#define SPHEREH

#include "intersectable.h"
#include "ray.h"
#include "vec3.h"

class Sphere: public Intersectable {
public:
    Sphere() {}
    Sphere(Vec3 position, float radius) { pos = position; r = radius; }

    // intersect Ray (Vector with direction) and Sphere.
    // A sphere is defined as the centre of all points (x, y, z) which fulfill:
    //
    // (x - cx)^2 + (y - cy)^2 + (z - cz)^2 = r^2
    //
    // which can be written as an implicit equation:
    //
    // (P - C)^2 - r^2 = 0
    //
    // enabling us to extract the common point P between the Ray and Sphere.
    // A point in the Ray is given by:
    //
    // P = S + tD
    //
    // Where S is the origin point and D the direction vector.
    // Now we can solve for t to find out whether there's an intersection
    // by replacing the point definition:
    //
    // (S + tD - C)^2 - r^2 = 0
    //
    // which solving for t leads to a 2nd degree equation:
    //
    // (S + tD)^2 + C^2 - 2C|S + tD| - r^2 = 0
    // SS + ttDD + 2StD + CC - 2CS + 2CtD - rr = 0
    // (t^2)DD + (t)(2SD + 2CD) + (CC - 2CS - rr) = 0
    // (t^2)DD + (t)(2D(S + C)) + (C(C - 2S) - rr)
    //      ^            ^               ^
    //      a            b               c
    //
    // Iff t >= 0 there's one (== 0) or more (> 0) intersection points.
    bool intersects(const Ray &ray, float t_min, float t_max, Intersection& i) const {
        Vec3 sc = ray.origin() - pos;
        float a = Vec3::dot(ray.direction(), ray.direction());
        float b = Vec3::dot(sc, ray.direction());
        float c = Vec3::dot(sc, sc) - r * r;
        float discriminant = b * b - a * c;

        if (discriminant > 0) {
            float t = (-b - sqrt(discriminant)) / a;
            if (t <= t_min || t >= t_max) {
                t = (-b - sqrt(discriminant)) / a;
                if (t <= t_min || t >= t_max) {
                    return false;
                }
            }
            i.t = t;
            i.point = ray.point_at(t);
            i.normal = (i.point - pos) / r;
            return true;
        }
        return false;
    }

private:
    Vec3 pos;
    float r;
};

#endif