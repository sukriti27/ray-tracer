#ifndef SHAPESLISTH
#define SHAPESLISTH

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"

namespace rt{

class ShapesList: public Shape {
    public:
        ShapesList() {}
        ShapesList(Shape **l, int n) {list = l; list_size = n; }
        virtual bool hit(
            const Ray& r, float tmin, float tmax, Hit& rec) const;
        virtual bool bounding_box(aabb& box) const;
        Shape **list;
        int list_size;
};

bool ShapesList::bounding_box(aabb& box) const {
    if (list_size < 1) return false;
    aabb temp_box;
    bool first_true = list[0]->bounding_box(temp_box);
    if (!first_true)
        return false;
    else 
        box = temp_box;
    for (int i = 1; i < list_size; i++) {
        if(list[i]->bounding_box(temp_box)) {
            Vec3f small( ffmin(box.min().x, temp_box.min().x),
                ffmin(box.min().y, temp_box.min().y),
                ffmin(box.min().z, temp_box.min().z));
            Vec3f big  ( ffmax(box.max().x, temp_box.max().x),
                ffmax(box.max().y, temp_box.max().y),
                ffmax(box.max().z, temp_box.max().z));
            box = aabb(small,big);
        }
        else
            return false;
    }
    return true;
}

bool ShapesList::hit(const Ray& r, float t_min, float t_max,
                        Hit& rec) const {

    // To store information about the closest intersection i.e. point of intersection, normal and distance from origin
    Hit temp_rec;

    bool hit_anything = false;

    double closest_so_far = t_max;

    // Iterate over the shapes in the list
    for (int i = 0; i < list_size; i++) 
    {
        // If ray hits a closer objects
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) 
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
};
}

#endif