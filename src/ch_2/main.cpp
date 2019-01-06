#include <iostream>
#include "vec3.h"

int main() {
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            int k = 255.99;
            int ir = int(col[0] * k);
            int ig = int(col[1] * k);
            int ib = int(col[2] * k);

            std::cout << ir << " " << ig << "  " << ib << "\n";
        }
    }
}