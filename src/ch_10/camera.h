#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "vec3.h"

class Camera {
public:
    Camera() {
        origin = Vec3(0.0, 0.0, 0.0);
        lower_left_corner = Vec3(-2.0, -1.0, -1.0);
        horizontal = Vec3(4.0, 0.0, 0.0);
        vertical = Vec3(0.0, 2.0, 0.0);
    }
    Camera(Vec3 look_from, Vec3 look_to, float vertical_fov, float aspect_ratio) { // vertical_fov is top to bottom in degrees
        Vec3 u, v, w;
        Vec3 v_up = Vec3(0, 1, 0);
        float theta = vertical_fov * M_PI/180;
        float half_height = tan(theta / 2);
        float half_width = aspect_ratio * half_height;
        w = Vec3::normalized(look_from - look_to);
        u = Vec3::normalized(Vec3::cross(v_up, w));
        v = Vec3::cross(w, u);
        lower_left_corner = look_from - half_width * u - half_height * v - w;
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
        origin = look_from;
        //lower_left_corner = Vec3(-half_width, -half_height, -1.0);
        //horizontal = Vec3(2 * half_width, 0.0, 0.0);
        //vertical = Vec3(0.0, 2 * half_height, 0.0);
        //origin = Vec3(0.0, 0.0, 0.0);

    }

    Ray get_ray(float u, float v) {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
};

#endif