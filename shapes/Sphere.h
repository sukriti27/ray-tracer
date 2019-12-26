/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "core/Material.h"
#include "rapidjson/document.h"

namespace rt
{

class Sphere : public Shape
{

  public:
	Sphere(){};

	~Sphere(){};

	bool hit(const Ray &r, float tmin, float tmax, Hit &rec) const;
	bool bounding_box(aabb &box) const;
	void setCenter(Vec3f c);
	void setRadius(float r);

  private:
	Vec3f center;
	float radius;
};

} //namespace rt

#endif /* SPHERE_H_ */
