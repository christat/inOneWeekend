#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "scene.h"
#include "vec3.h"

Vec3 color(const Ray &r, Scene &s) {
    Intersection intersection;
    if (s.intersects(r, 0.0, MAXFLOAT, intersection)) {
        return 0.5 * Vec3(
            intersection.normal.x() + 1.0,
            intersection.normal.y() + 1.0,
            intersection.normal.z() + 1.0
        );
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
    const int k = 255.99;

    // define a 2x4 rectangle (in whatever units the 3D space lays).
    // the image plane is centered on the y axis (hence x = -2.0)
    // and at a distance of z = -1.0 (negative so that we respect the Right-hand rule).
    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0); // camera position

    Intersectable *list[2];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
    Scene scene(list, 2);

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    // "poke" rays through the grid of pixels; top-down, left to right.
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3 col = color(r, scene);

            int ir = int(col[0] * k);
            int ig = int(col[1] * k);
            int ib = int(col[2] * k);

            std::cout << ir << " " << ig << "  " << ib << "\n";
        }
    }
}