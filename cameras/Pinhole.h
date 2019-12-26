/*
 * Pinhole.h
 *
 *
 */

#ifndef PINHOLE_H_
#define PINHOLE_H_

#include "core/Camera.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

namespace rt
{

class Pinhole : public Camera
{
  public:
	Pinhole();
	Pinhole(int width, int height, int fov);
	~Pinhole(){};
	void printCamera();
	Ray get_ray(float u, float v);
	void setParameters(Vec3f lookfrom, Vec3f lookat, Vec3f vup)
	{
		this->lookfrom = lookfrom;
		this->lookat = lookat;
		this->vup = vup;

		float theta = fov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = width / height * half_height;

		Vec3f u, v, w;
		w = (lookfrom - lookat).normalize();
		u = (vup.crossProduct(w)).normalize();
		v = w.crossProduct(u);

		// Position of the camera
		origin = lookfrom;
		// Dimensions of the screen
		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2 * half_width * u;
		vertical = 2 * half_height * v;
	};

	Vec3f origin;
	Vec3f lower_left_corner;
	Vec3f horizontal;
	Vec3f vertical;
	Vec3f lookfrom;
	Vec3f lookat;
	Vec3f vup;
};

} //namespace rt

#endif /* PINHOLE_H_ */
