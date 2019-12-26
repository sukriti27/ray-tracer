/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"

namespace rt
{

/**
	 * Computes whether a ray hit the specific instance of a Triangle shape and finds the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 * 
	 * @param t_min and t_max are valid range of values for t. If t does not lie in the range, no intersection
	 *
	 * @param hit or intersection information
	 * 
	 * @return true if ray intersects with triangle, false otherwise
	 *
	 */

bool Triangle::hit(const Ray &r, float t_min, float t_max, Hit &rec) const
{
        float kEpsilon = 1e-8;
        float u, v;

        Vec3f v0v1 = v1 - v0;
        Vec3f v0v2 = v2 - v0;
        Vec3f pvec = r.direction().crossProduct(v0v2);
        float det = v0v1.dotProduct(pvec);
        // if the determinant is negative the triangle is backfacing
        // if the determinant is close to 0, the ray misses the triangle
        if (det < kEpsilon)
                return false;
        // ray and triangle are parallel if det is close to 0
        if (fabs(det) < kEpsilon)
                return false;
        float invDet = 1 / det;

        Vec3f tvec = r.origin() - v0;
        u = tvec.dotProduct(pvec) * invDet;
        if (u < 0 || u > 1)
                return false;

        Vec3f qvec = tvec.crossProduct(v0v1);
        v = r.direction().dotProduct(qvec) * invDet;
        if (v < 0 || u + v > 1)
                return false;

        float temp = v0v2.dotProduct(qvec) * invDet;
        rec.t = temp;
        rec.point = r.point_at_parameter(rec.t);
        Vec3f N = v0v1.crossProduct(v0v2);
        N /= N.length();
        rec.normal = N;
        rec.material = getMaterial();

        if (hasUV)
        {
                float w = 1 - u - v;
                rec.u = u * uv0.x + v * uv1.x + w * uv2.x;
                rec.v = u * uv0.y + v * uv1.y + w * uv2.y;
        }

        return true;
}

// Bounding box for the triangle
bool Triangle::bounding_box(aabb &box) const
{
        float temp = std::max(v0.x, v1.x);
        float xmax = std::max(temp, v2.x);

        temp = std::min(v0.x, v1.x);
        float xmin = std::min(temp, v2.x);

        temp = std::max(v0.y, v1.y);
        float ymax = std::max(temp, v2.y);

        temp = std::min(v0.y, v1.y);
        float ymin = std::min(temp, v2.y);

        temp = std::max(v0.z, v1.z);
        float zmax = std::max(temp, v2.z);

        temp = std::min(v0.z, v1.z);
        float zmin = std::min(temp, v2.z);

        box = aabb(Vec3f(xmin, ymin, zmin), Vec3f(xmax, ymax, zmax));
        return true;
}

// Initialize the vertices of the triangle
void Triangle::setVertices(Vec3f _v0, Vec3f _v1, Vec3f _v2)
{
        v0 = _v0;
        v1 = _v1;
        v2 = _v2;
}

void Triangle::setUV(Vec2f _uv0, Vec2f _uv1, Vec2f _uv2)
{
        uv0 = _uv0;
        uv1 = _uv1;
        uv2 = _uv2;
        hasUV = true;
}

} //namespace rt
