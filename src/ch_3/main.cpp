#include <iostream>
#include "ray.h"

Vec3 color(const Ray &r) {
    Vec3 unit_direction = r.direction().normalized();

    // -1.0 < unit_direction < 1.0; we want it in a 0.0 < t < 1.0 scale.
    float t = 0.5 * (unit_direction.y() + 1.0);

    // color lerp; the more "straight" the direction, the greater the blue contribution.
    return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 200;
    int ny = 100;

    // define a 2x4 rectangle (in whatever units the 3D space lays).
    // the image plane is centered on the y axis (hence x = -2.0)
    // and at a distance of z = -1.0 (negative so that we respect the Right-hand rule).
    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0); // camera position

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    // "poke" rays through the grid of pixels; top-down, left to right.
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3 col = color(r);
            int k = 255.99;
            int ir = int(col[0] * k);
            int ig = int(col[1] * k);
            int ib = int(col[2] * k);

            std::cout << ir << " " << ig << "  " << ib << "\n";
        }
    }
}