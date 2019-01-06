#include <iostream>

#include "camera.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "vec3.h"

Vec3 random_from_tangent_unit_sphere() {
    Vec3 random;
    do {
        random = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1.0, 1.0, 1.0);
    } while (random.length_squared() >= 1.0);
    return random;
}

Vec3 get_color(const Ray &r, Scene &s) {
    Intersection intersection;
    if (s.intersects(r, 0.001, MAXFLOAT, intersection)) {
        Vec3 target = intersection.point + intersection.normal + random_from_tangent_unit_sphere();
        return 0.5 * get_color(Ray(intersection.point, target - intersection.point), s);
    }

    Vec3 unit_direction = r.direction().normalized();

    // -1.0 < unit_direction < 1.0; convert to 0.0 < t < 1.0 scale below:
    float t = 0.5 * (unit_direction.y() + 1.0);

    // color lerp; the more "straight" the direction, the greater the blue contribution.
    return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main() {
    const int nx = 200;
    const int ny = 100;
    const int ns = 100;
    const int k = 255.99;

    Intersectable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Scene scene(list, 2);
    Camera camera;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    // "poke" rays through the grid of pixels; top-down, left to right.
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            // For each pixel on the screen, ns rays are shot and their
            // color contributions averaged, creating an "antialias" blur on shape edges.
            Vec3 color(0.0, 0.0, 0.0);
            for (int sample = 0; sample < ns; sample++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray r = camera.get_ray(u, v);
                Vec3 point = r.point_at(2.0);
                color += get_color(r, scene);
            }
            color /= float(ns);
            color = Vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
            int ir = int(color[0] * k);
            int ig = int(color[1] * k);
            int ib = int(color[2] * k);

            std::cout << ir << " " << ig << "  " << ib << "\n";
        }
    }
}