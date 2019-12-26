/*
 * ThinLens.h
 *
 *
 */

#ifndef THINLENS_H_
#define THINLENS_H_

#include "core/Camera.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

namespace rt
{

class ThinLens : public Camera
{
  public:
	//
	// Constructors
	//
	ThinLens();
	ThinLens(int width, int height, int fov);

	//
	//Destructor
	//
	~ThinLens(){};

	//
	// print function (implementing abstract function of base class)
	//
	void printCamera();
	Ray get_ray(float u, float v);

	void setParameters(Vec3f lookfrom, Vec3f lookat, Vec3f vup, float aperture, float focus_dist)
	{
		lens_radius = aperture / 2;

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
		lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
		horizontal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;

		this->lookfrom = lookfrom;
		this->lookat = lookat;
		this->vup = vup;
		this->aperture = aperture;
		this->focus_dist = focus_dist;
		this->u = u;
		this->v = v;
		this->w = w;
	};

	Vec3f origin;
	Vec3f lower_left_corner;
	Vec3f horizontal;
	Vec3f vertical;
	Vec3f lookfrom;
	Vec3f lookat;
	Vec3f vup;
	Vec3f u, v, w;
	float aperture, focus_dist;
	float lens_radius;
};

} //namespace rt

#endif /* THILENS_H_ */
