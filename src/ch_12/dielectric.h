#ifndef DIELECTRICH
#define DIELECTRICH

#include <math.h>
#include "intersectable.h"
#include "material.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"

float schlick(float cosine, float ref_idx) {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class Dielectric: public Material {
public:
    Dielectric(float refractive_index) { ri = refractive_index; }
    bool scatter(const Ray& r_in, const Intersection& i, Vec3& attenuation, Ray& scattered) const {
        Vec3 outward_normal;
        Vec3 reflected = reflect(r_in.direction(), i.normal);
        float ni_over_nt;
        attenuation = Vec3(1.0, 1.0, 1.0);
        Vec3 refracted;
        float reflect_prob;
        float cosine;
        if (Vec3::dot(r_in.direction(), i.normal) > 0) {
            outward_normal = -i.normal;
            ni_over_nt = ri;
            cosine = Vec3::dot(r_in.direction(), i.normal) / r_in.direction().length();
            cosine = sqrt(1 - ri * ri * (1 - cosine * cosine));
        } else {
            outward_normal = i.normal;
            ni_over_nt = 1.0 / ri;
            cosine = -Vec3::dot(r_in.direction(), i.normal) / r_in.direction().length();
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ri);
        } else {
            reflect_prob = 1.0;
        }
        if (drand48() < reflect_prob) {
             scattered = Ray(i.point, reflected);
        } else {
            scattered = Ray(i.point, refracted);
        }
        return true;
    }

private:
    float ri;
};

#endif