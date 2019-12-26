/*
 * BVH.cpp
 *
 *
 */
#include "BVH.h"


namespace rt{

bool bvh_node::bounding_box(aabb& b) const {
    b = box;
    return true;
};

bool bvh_node::hit(const Ray& r, float t_min, float t_max, Hit& rec) const {
    if (box.hit(r, t_min, t_max)) {
        Hit left_rec, right_rec;
        bool hit_left = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);
        if (hit_left && hit_right) {
            if (left_rec.t < right_rec.t) 
                rec = left_rec;
            else 
                rec = right_rec;
            return true;
        }
        else if (hit_left) {
            rec = left_rec;
            return true;
        }
        else if (hit_right) {
            rec = right_rec;
            return true;
        }
        else 
            return false;
    }
    else return false;
};

int box_x_compare (const void * a, const void * b) {
        aabb box_left, box_right;
        Shape *ah = *(Shape**)a;
        Shape *bh = *(Shape**)b;
        if(!ah->bounding_box(box_left) || !bh->bounding_box(box_right))
                        std::cerr << "no bounding box in bvh_node constructor\n";
        if ( box_left.min().x - box_right.min().x < 0.0  )
            return -1;
        else
            return 1;
};

int box_y_compare (const void * a, const void * b)
{
        aabb box_left, box_right;
        Shape *ah = *(Shape**)a;
        Shape *bh = *(Shape**)b;
        if(!ah->bounding_box(box_left) || !bh->bounding_box(box_right))
                        std::cerr << "no bounding box in bvh_node constructor\n";
        if ( box_left.min().y - box_right.min().y < 0.0  )
            return -1;
        else
            return 1;
}
int box_z_compare (const void * a, const void * b)
{
        aabb box_left, box_right;
        Shape *ah = *(Shape**)a;
        Shape *bh = *(Shape**)b;
        if(!ah->bounding_box(box_left) || !bh->bounding_box(box_right))
                        std::cerr << "no bounding box in bvh_node constructor\n";
        if ( box_left.min().z - box_right.min().z < 0.0  )
            return -1;
        else
            return 1;
}


bvh_node::bvh_node(Shape **l, int n) {
    int axis = int(3*random_double());
    if (axis == 0)
       qsort(l, n, sizeof(Shape *), box_x_compare);
    else if (axis == 1)
       qsort(l, n, sizeof(Shape *), box_y_compare);
    else
       qsort(l, n, sizeof(Shape *), box_z_compare);
    if (n == 1) {
        left = right = l[0];
    }
    else if (n == 2) {
        left = l[0];
        right = l[1];
    }
    else {
        left = new bvh_node(l, n/2);
        right = new bvh_node(l + n/2, n - n/2);
    }
    aabb box_left, box_right;
    if(!left->bounding_box(box_left) || !right->bounding_box(box_right))
        std::cerr << "no bounding box in bvh_node constructor\n"; 

    Vec3f small( ffmin(box_left.min().x, box_right.min().x),
                ffmin(box_left.min().y, box_right.min().y),
                ffmin(box_left.min().z, box_right.min().z));
    Vec3f big  ( ffmax(box_left.max().x, box_right.max().x),
                ffmax(box_left.max().y, box_right.max().y),
                ffmax(box_left.max().z, box_right.max().z));
    box = aabb(small,big);
};





} //namespace rt


