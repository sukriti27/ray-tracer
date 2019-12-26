/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"
#include "rapidjson/document.h"

namespace rt
{

void get_sphere_uv(const Vec3f &p, float &u, float &v)
{
	float phi = atan2(p.z, p.x);
	float theta = asin(p.y);
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

/**
	 * Bounding box for sphere
	 */
bool Sphere::bounding_box(aabb &box) const
{
	box = aabb(center - Vec3f(radius, radius, radius), center + Vec3f(radius, radius, radius));
	return true;
}

/**
	 * Computes whether a ray hit the specific instance of a sphere shape and finds the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 * 
	 * @param t_min and t_max are valid range of values for t. If t does not lie in the range, no intersection
	 *
	 * @param hit or intersection information
	 * 
	 * @return true if ray intersects with sphere, false otherwise
	 *
	 */

bool Sphere::hit(const Ray &r, float t_min, float t_max, Hit &rec) const
{
	// To check if the input ray intersects with the sphere
	// Ray of form p(t) = A + t*B
	// Sphere defined by (x-Cx)^2 + (y-Cy)^2 + (z-Cz)^2 = R^2
	// center(Cx, Cy, Cz), radius R
	// We get a quadratic equation and we can solve for t

	// A - C
	Vec3f oc = r.origin() - center;

	// a = B.B
	float a = r.direction().dotProduct(r.direction());

	// b = B.(A-C)
	float b = oc.dotProduct(r.direction());

	// c = (A-C).(A-C) - R^2
	float c = oc.dotProduct(oc) - radius * radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			// Finding p(t) when we have t
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);

			// Finding normal, divide by R for unit length
			rec.normal = (rec.point - center) /= radius;

			rec.material = getMaterial();
			get_sphere_uv((rec.point - center) /= radius, rec.u, rec.v);

			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);
			rec.normal = (rec.point - center) /= radius;
			rec.normal /= rec.normal.length();
			rec.material = getMaterial();
			get_sphere_uv((rec.point - center) /= radius, rec.u, rec.v);
			return true;
		}
	}

	// No intersection
	return false;
}

void Sphere::setCenter(Vec3f c) { center = c; }
void Sphere::setRadius(float r) { radius = r; }

} //namespace rt
