/*
 * RayTracer.cpp
 *
 */
#include "RayTracer.h"
#include "RayHitStructs.h"
#include "Shape.h"
#include "shapes/TriangleMesh.h"
#include "shapes/ShapesList.h"
#include "lights/PointLight.h"
#include "lights/AreaLight.h"
#include "materials/BlinnPhong.h"
#include "materials/Reflective.h"
#include "materials/Transparent.h"
#include "LightSource.h"
#include "shapes/BVH.h"
#include "cfloat"
#include <cstdlib>
#include <time.h>

inline float clamp(const float &lo, const float &hi, const float &v)
{
	return std::max(lo, std::min(hi, v));
}

namespace rt
{

Vec3f reflect(const Vec3f &I, const Vec3f &N)
{
	return I - 2 * I.dotProduct(N) * N;
}

Vec3f refract(const Vec3f &I, const Vec3f &N, const float &ior)
{
	float cosi = clamp(-1, 1, I.dotProduct(N));
	float etai = 1;
	float etat = ior;
	Vec3f n = N;
	if (cosi < 0)
	{
		cosi = -cosi;
	}
	else
	{
		std::swap(etai, etat);
		n = -N;
	}
	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n;
}

void fresnel(const Vec3f &I, const Vec3f &N, const float &ior, float &kr)
{
	float cosi = clamp(-1, 1, I.dotProduct(N));
	float etai = 1, etat = ior;
	if (cosi > 0)
	{
		std::swap(etai, etat);
	}
	// Compute sini using Snell's law
	float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1)
	{
		kr = 1;
	}
	else
	{
		float cost = sqrtf(std::max(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
}

Vec3f RayTracer::color(const Ray &r, Shape *world, std::vector<LightSource *> lights, int nbounces, Vec3f backgroundColor, const int &depth)
{
	if (depth > nbounces)
		return backgroundColor;

	Hit rec;
	Vec3f pixelbuffer;

	// If ray intersects with any shape in the list of shapes
	if (world->hit(r, 0, FLT_MAX, rec))
	{
		pixelbuffer = Vec3f(0, 0, 0);
		if (rec.material->getType().compare("blinnphong") == 0)
		{
			Vec3f diffuse(0, 0, 0), specular(0, 0, 0);
			BlinnPhong *phong = dynamic_cast<BlinnPhong *>(rec.material);
			Vec3f color = phong->hasTextureValue() ? phong->getTextureRGB(rec.u, rec.v) : phong->getDiffuseColor();

			for (LightSource *light : lights)
			{
				if (light->getType().compare("pointlight") == 0)
				{
					PointLight *p = dynamic_cast<PointLight *>(light);
					float dot = rec.normal.dotProduct(-p->getPosition()) >= 0 ? rec.normal.dotProduct(-p->getPosition()) : 0;
					Ray r1(rec.point, -p->getPosition());
					Hit rec1;
					int vis = world->hit(r1, 0.0001, FLT_MAX, rec1) ? 0 : 1;

					// compute diffuse component
					Vec3f _diffuse = color * p->getIntensity();
					_diffuse *= dot;
					_diffuse *= vis;
					diffuse = diffuse + _diffuse;

					// compute the specular component
					// what would be the ideal reflection direction for this light ray
					Vec3f R = reflect(p->getPosition(), rec.normal);
					Vec3f _specular = vis * p->getIntensity();
					_specular *= std::pow(std::max(0.f, R.dotProduct(-r.direction())), phong->getSpecularExponent());
					specular = specular + _specular;
				}
				else if (light->getType().compare("arealight") == 0)
				{
					AreaLight *p = dynamic_cast<AreaLight *>(light);
					int ns = 1;
					for (int i = 0; i < ns; i++)
					{
						Vec3f point = p->getRandomPoint();
						Vec3f ShadowRayDirection = -(rec.point - point).normalize();
						Vec3f direction = p->getDirection();
						float dot = rec.normal.dotProduct(-direction) >= 0 ? rec.normal.dotProduct(-direction) : 0;
						Ray r1(rec.point, ShadowRayDirection);
						Hit rec1;
						int vis = world->hit(r1, 0.001, FLT_MAX, rec1) ? 0 : 1;

						// compute diffuse component
						Vec3f _diffuse = color * p->getIntensity();
						_diffuse *= dot;
						_diffuse *= vis;
						diffuse = diffuse + _diffuse;

						// compute the specular component
						Vec3f R = reflect(direction, rec.normal);
						Vec3f _specular = vis * p->getIntensity();
						_specular *= std::pow(std::max(0.f, R.dotProduct(-r.direction())), phong->getSpecularExponent());
						specular = specular + _specular;
					}
					diffuse /= (float)ns;
					specular /= (float)ns;
				}
			}
			pixelbuffer = diffuse * phong->getKd() + specular * phong->getKs();
		}
		else if (rec.material->getType().compare("reflective") == 0)
		{
			Ray R;
			float bias = 0.1;
			// Origin
			R.A = rec.point + rec.normal * bias;
			// Direction
			R.B = r.direction() - 2 * r.direction().dotProduct(rec.normal) * rec.normal;
			pixelbuffer = pixelbuffer + 0.9 * color(R, world, lights, nbounces, backgroundColor, depth + 1);
		}
		else if (rec.material->getType().compare("transparent") == 0)
		{
			Transparent *tr = dynamic_cast<Transparent *>(rec.material);

			Vec3f refractionColor = 0;
			// compute fresnel
			float kr;
			fresnel(r.direction(), rec.normal, tr->getRefractiveIndex(), kr);
			bool outside = r.direction().dotProduct(rec.normal) < 0;
			Vec3f bias = 0.0001 * rec.normal;
			// compute refraction if it is not a case of total internal reflection
			if (kr < 1)
			{
				Vec3f refractionDirection = refract(r.direction(), rec.normal, tr->getRefractiveIndex()).normalize();
				Vec3f refractionRayOrig = outside ? rec.point - bias : rec.point + bias;
				Ray refractionRay(refractionRayOrig, refractionDirection);
				refractionColor = color(refractionRay, world, lights, nbounces, backgroundColor, depth + 1);
			}

			Vec3f reflectionDirection = reflect(r.direction(), rec.normal).normalize();
			Vec3f reflectionRayOrig = outside ? rec.point + bias : rec.point - bias;
			Ray reflectionRay(reflectionRayOrig, reflectionDirection);
			Vec3f reflectionColor = color(reflectionRay, world, lights, nbounces, backgroundColor, depth + 1);

			// mix the two
			pixelbuffer = pixelbuffer + (reflectionColor * kr + refractionColor * (1 - kr));
		}
		else
		{
			pixelbuffer = Vec3f(1, 1, 1);
		}
	}
	// If ray does not intersect any shape in the list of shapes
	else
	{
		pixelbuffer = backgroundColor;
	}
	return pixelbuffer;
}

/**
	 * Performs ray tracing to render a photorealistic scene
	 *
	 * @param camera the camera viewing the scene
	 * @param scene the scene to render, including objects and lightsources
	 * @param nbounces the number of bounces to consider for raytracing
	 *
	 * @return a pixel buffer containing pixel values in linear RGB format
	 */
Vec3f *RayTracer::render(Camera *camera, Scene *scene, int nbounces)
{

	// Number of pixels in image is nx*ny
	int nx = camera->getWidth();
	int ny = camera->getHeight();

	// Vector array to store the color of pixels. For each pixel, the r, g, b values will be in between 0 and 1.
	Vec3f *pixelbuffer = new Vec3f[nx * ny];

	// To keep track of the last index with color in the pixelbuffer
	int counter = 0;

	std::vector<Shape *> shapes = scene->getShapes();
	int i = 0;
	Shape *list[shapes.size()];
	for (Shape *s : shapes)
	{
		list[i] = s;
		i++;
	}

	int j = 0;
	Shape **lst = new Shape *[shapes.size()];
	for (Shape *s : shapes)
	{
		lst[j] = s;
		j++;
	}

	Shape *world = new ShapesList(list, i);
	bvh_node *root_node = new bvh_node(lst, j);

	std::vector<LightSource *> lights = scene->getLights();

	clock_t t1, t2;
	t1 = clock();

	// Traverse from top left corner to bottom right corner covering the entire screen
	// j from height - 1 to 0
	// i from 0 to width - 1 for each j
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			// Convert pixel coordinates in raster space to world space
			// u, v will be in between 0 and 1

			int ns = 50;
			pixelbuffer[counter] = Vec3f(0, 0, 0);
			Vec3f backgroundColor = scene->getBackgroundColor();
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + (rand() / (RAND_MAX + 1.0))) / float(nx);
				float v = float(j + (rand() / (RAND_MAX + 1.0))) / float(ny);
				Ray r = camera->get_ray(u, v);
				// root_node for bvh, world otherwise
				pixelbuffer[counter] = pixelbuffer[counter] + color(r, world, lights, nbounces, backgroundColor);
			}
			pixelbuffer[counter] /= float(ns);

			// Increment counter for pixelbuffer
			counter++;
		}
	}

	t2 = clock();
	double time_dif = (double)(t2 - t1) / CLOCKS_PER_SEC;
	std::cout << "Time taken is : " << time_dif << std::endl;

	return pixelbuffer;
}

/**
	 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
	 *
	 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
	 *
	 * @return the tonemapped image
	 */
Vec3f *RayTracer::tonemap(Vec3f *pixelbuffer, int size)
{
	for (int i = 0; i < size; i++)
		pixelbuffer[i] *= 255.99;

	return pixelbuffer;
}

} //namespace rt
