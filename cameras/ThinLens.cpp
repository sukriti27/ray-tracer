/*
 * ThinLens.cpp
 *
 *
 */
#include <iostream>

#include "ThinLens.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

namespace rt
{

inline double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

inline float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

Vec3f method_two(float radius)
{

	float r = radius * sqrt(random_double());
	float theta = random_double() * 2 * M_PI;
	float x = r * cos(theta);
	float y = r * sin(theta);
	return Vec3f(x, y, 0);
}

Vec3f method_one(float radius)
{
	float x, y;
	do
	{
		x = RandomFloat(-radius, radius);
		y = RandomFloat(-radius, radius);
	} while (sqrt(x * x + y * y) > radius);
	return Vec3f(x, y, 0);
}

//
// ThinLens constructor (example)
//
ThinLens::ThinLens(int width, int height, int fov) : Camera(width, height, fov)
{
	setHeight(height);
	setWidth(width);
	this->fov = fov;
}

// To get ray for a given pixel
Ray ThinLens::get_ray(float u, float v)
{
	Vec3f rd = method_one(lens_radius);
	//Vec3f rd = method_two(lens_radius);
	Vec3f offset = u * rd.x + v * rd.y;
	return Ray(origin + offset, lower_left_corner + u * horizontal + v * vertical - origin - offset);
}

/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
void ThinLens::printCamera()
{
	printf("I am a thin lens camera! \n");
	printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
}

} //namespace rt
