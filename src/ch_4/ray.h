#ifndef RAYH
#define RAYH
#include "vec3.h"

class Ray {
public:
    Ray() {}
    // A ray is defined by a point (origin) and a direction vector.
    Ray(const Vec3& origin, const Vec3& direction) { o = origin; d = direction; }

    Vec3 o;
    Vec3 d;
    
    Vec3 origin() const { return o; }
    Vec3 direction() const { return d; }

    // Any point belonging to the Ray must fulfill the equation:
    // p = origin + t * direction
    Vec3 point_at(float t) const { return o + t * d; }
};

#endif