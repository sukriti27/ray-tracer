/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Shape.h"
#include "core/Scene.h"

namespace rt
{

/*
 * Raytracer class declaration
 */
class RayTracer
{
public:
	RayTracer();

	static Vec3f color(const Ray &r, Shape *world, std::vector<LightSource *> lights, int nbounces, Vec3f backgroundColor, const int &depth = 0);
	static Vec3f *render(Camera *camera, Scene *scene, int nbounces);
	static Vec3f *tonemap(Vec3f *pixelbuffer, int size);

private:
};

} //namespace rt

#endif /* RAYTRACER_H_ */
