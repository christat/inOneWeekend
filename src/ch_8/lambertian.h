#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "intersectable.h"
#include "material.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

class Lambertian: public Material {
public:
    Lambertian(const Vec3& a) { albedo = a; }
    bool scatter(const Ray& r_in, const Intersection& i, Vec3& attenuation, Ray& scattered) const {
        Vec3 target = i.point + i.normal + random_from_tangent_unit_sphere();
        scattered = Ray(i.point, target - i.point);
        attenuation = albedo;
        return true;
    }

private:
    Vec3 albedo;
};

#endif