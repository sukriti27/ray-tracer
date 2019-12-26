/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"

namespace rt
{

class Triangle : public Shape
{

  public:
	Triangle() : Shape(){};

	~Triangle(){};

	bool hit(const Ray &r, float tmin, float tmax, Hit &rec) const;
	bool bounding_box(aabb &box) const;
	void setVertices(Vec3f _v0, Vec3f _v1, Vec3f _v2);
	void setUV(Vec2f _uv0, Vec2f _uv1, Vec2f _uv2);

  private:
	Vec3f v0, v1, v2;
	Vec2f uv0, uv1, uv2;
	bool hasUV = false;
};

} //namespace rt

#endif /* TRIANGLE_H_ */
