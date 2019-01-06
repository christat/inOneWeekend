#include <iostream>

#include "camera.h"
#include "dielectric.h"
#include "lambertian.h"
#include "metal.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "utils.h"
#include "vec3.h"

// recursive ray tracing call, checks object intersection and material ray scattering.
Vec3 get_color(const Ray &r, Scene &scene, int depth) {
    Intersection intersection;
    if (scene.intersects(r, 0.001, MAXFLOAT, intersection)) {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && intersection.mat_ptr->scatter(r, intersection, attenuation, scattered)) {
            return attenuation * get_color(scattered, scene, depth + 1);
        }
        return Vec3(0, 0, 0);
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

    const int list_length = 5;
    Intersectable *list[list_length];
    list[0] = new Sphere(Vec3(0.0, 0.0, -1.0), 0.5, new Lambertian(Vec3(0.1, 0.2, 0.5)));
    list[1] = new Sphere(Vec3(0.0, -100.5, -1.0), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vec3(1.0, 0.0, -1.0), 0.5, new Metal(Vec3(0.8, 0.6, 0.2)));
    list[3] = new Sphere(Vec3(-1.0, 0.0, -1.0), 0.5, new Dielectric(1.5));
    list[4] = new Sphere(Vec3(-1.0, 0.0, -1.0), -0.45, new Dielectric(1.5));
    Scene scene(list, list_length);
    Camera cam;

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
                Ray r = cam.get_ray(u, v);
                Vec3 point = r.point_at(2.0);
                color += get_color(r, scene, 0);
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