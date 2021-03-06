#include <iostream>

int main() {
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float r = float(i) /float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            float maxRgb = 255.99;
            int ir = int(maxRgb * r);
            int ig = int(maxRgb * g);
            int ib = int(maxRgb * b);
            std::cout << ir << " " << ig << "  " << ib << "\n";
        }
    }
}