#ifndef INTERSECTABLEH
#define INTERSECTABLEH

#include "ray.h"
#include "vec3.h"

struct Intersection {
    float t;
    Vec3 point;
    Vec3 normal;
};

class Intersectable {
public:
    virtual bool intersects(const Ray &r, float t_min, float t_max, Intersection& i) const = 0;
};

#endif