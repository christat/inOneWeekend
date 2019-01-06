#ifndef SCENEH
#define SCENEH

#include "intersectable.h"

class Scene: public Intersectable {
public:
    Scene() {}
    Scene(Intersectable **l, int n) { list = l; list_size = n; }

    bool intersects(const Ray &r, float t_min, float t_max, Intersection& intersection) const {
        Intersection temp;
        bool has_intersected = false;
        double nearest_t = t_max;
        for (int i = 0; i < list_size; i++) {
            if(list[i]->intersects(r, t_min, nearest_t, temp)) {
                has_intersected = true;
                nearest_t = temp.t;
                intersection = temp;
            }
        }
        return has_intersected;
    }

private:
    Intersectable **list;
    int list_size;
};

#endif