#ifndef METALH
#define METALH

#include "intersectable.h"
#include "material.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

class Metal: public Material {
public:
    Metal(const Vec3& a, float f = 0.0) {
        albedo = a;
        (f < 1.0) ? fuzz = f : fuzz = 1.0;
    }
    bool scatter(const Ray& r_in, const Intersection& i, Vec3& attenuation, Ray& scattered) const {
        Vec3 reflected = reflect(r_in.direction().normalized(), i.normal);
        scattered = Ray(i.point, reflected + fuzz * random_from_tangent_unit_sphere());
        attenuation = albedo;
        return (Vec3::dot(scattered.direction(), i.normal) > 0);
    }

private:
    Vec3 albedo;
    float fuzz;
};

#endif