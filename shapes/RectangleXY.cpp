/*
 * RectangleXY.cpp
 *
 *
 */
#include "RectangleXY.h"

namespace rt
{

/**
	 * Computes whether a ray hit the specific instance of a Rectangle shape and finds the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 * 
	 * @param t_min and t_max are valid range of values for t. If t does not lie in the range, no intersection
	 *
	 * @param hit or intersection information
	 * 
	 * @return true if ray intersects with Rectangle, false otherwise
	 *
	 */

bool RectangleXY::hit(const Ray &r, float t0, float t1, Hit &rec) const
{
    float t = (k - r.origin().z) / r.direction().z;
    if (t < t0 || t > t1)
        return false;

    float x = r.origin().x + t * r.direction().x;
    float y = r.origin().y + t * r.direction().y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    rec.t = t;
    rec.point = r.point_at_parameter(t);
    rec.normal = Vec3f(0, 0, 1);
    rec.material = getMaterial();

    rec.v = (x1 - rec.point.x) / (x1 - x0);
    rec.u = (y1 - rec.point.y) / (y1 - y0);

    return true;
}

/**
     * Bounding box for the rectangle
    */
bool RectangleXY::bounding_box(aabb &box) const
{
    box = aabb(Vec3f(x0, y0, k - 0.0001), Vec3f(x1, y1, k + 0.0001));
    return true;
};

/**
     * Initialize the fields in the RectangleXY class
     */
void RectangleXY::setVariables(float _x0, float _x1, float _y0, float _y1, float _k)
{
    x0 = _x0;
    x1 = _x1;
    y0 = _y0;
    y1 = _y1;
    k = _k;
}

} //namespace rt
