/*
 * BVH.h
 *
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include <cstdlib>
#include "core/Shape.h"

namespace rt{

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
};

class bvh_node: public Shape{
    public:
        bvh_node() {}
        bvh_node(Shape **l, int n);
        virtual bool hit(const Ray& r, float tmin, float tmax, Hit& rec) const;
        virtual bool bounding_box(aabb& box) const;
        Shape *left;
        Shape *right;
        aabb box;
};

} //namespace rt

#endif
