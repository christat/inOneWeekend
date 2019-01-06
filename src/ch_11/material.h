#ifndef MATERIALH
#define MATERIALH

#include "intersectable.h"
#include "ray.h"
#include "vec3.h"

class Material {
public:
    virtual bool scatter(const Ray& r_in, const Intersection& i, Vec3& attenuation, Ray& scattered) const = 0;
};

#endif