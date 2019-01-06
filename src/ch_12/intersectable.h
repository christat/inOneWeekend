#ifndef INTERSECTABLEH
#define INTERSECTABLEH

#include "ray.h"
#include "vec3.h"

class Material;

struct Intersection {
    float t;
    Vec3 point;
    Vec3 normal;
    Material *mat_ptr;
};

class Intersectable {
public:
    virtual bool intersects(const Ray &r, float t_min, float t_max, Intersection& i) const = 0;
};

#endif