/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"
#include "Material.h"

namespace rt
{

/*
 * Ray can be defined as a function p(t) = A + t*B
 * p(t) is a 3D point on the ray. We can get the value of p(t) using the function point_at_parameter(t), for which t is the input.
 * A is the ray origin and B is the ray direction.
 * t is the distance from the origin to p(t)
 */
struct Ray
{

  public:
	Ray() {}

	// Initialize ray with A, B i.e. origin and direction
	Ray(const Vec3f &a, const Vec3f &b)
	{
		A = a;
		B = b;
	}

	// Get A or origin of the ray
	Vec3f origin() const
	{
		return A;
	}

	// Get B or direction of the ray
	Vec3f direction() const
	{
		return B;
	}

	// Get the 3D point on the ray for a given value of t
	Vec3f point_at_parameter(float t) const
	{
		return A + t * B;
	}

	// Origin of ray
	Vec3f A;

	// Direction of ray
	Vec3f B;
};

struct Hit
{
	// point where ray hits a shape
	Vec3f point;

	// distance from origin
	float t;

	// normal to the surface at the intersection point
	Vec3f normal;

	Material *material;

	float u, v;
};

} // namespace rt

#endif /* CORE_RAYHITSTRUCTS_H_ */
