/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

#include "Pinhole.h"
#include "math/geometry.h"
#include "core/RayHitStructs.h"

namespace rt
{

//
// Pinhole constructor (example)
//
Pinhole::Pinhole(int width, int height, int fov) : Camera(width, height, fov)
{
	setHeight(height);
	setWidth(width);
	this->fov = fov;
}

// To get ray for a given pixel
Ray Pinhole::get_ray(float u, float v)
{
	return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}

/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
void Pinhole::printCamera()
{
	printf("I am a pinhole camera! \n");
	printf("width: %dpx, height: %dpx, fov:%d \n", width, height, fov);
}

} //namespace rt
