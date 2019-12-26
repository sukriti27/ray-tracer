/*
 * Shape.cpp
 *
 */
#include "Shape.h"
#include "Material.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"
#include "shapes/TriangleMesh.h"
#include "shapes/RectangleXY.h"
#include "rapidjson/document.h"

namespace rt
{

Shape *Shape::createShape(rapidjson::Value &shapeSpecs)
{
	// Check if shapetype is defined

	if (!shapeSpecs.HasMember("type"))
	{
		std::cerr << "Shape type not specified" << std::endl;
		exit(-1);
	}

	std::string shapeType = shapeSpecs["type"].GetString();

	// Return shape object based on shape specs

	// Sphere
	if (shapeType.compare("sphere") == 0)
	{

		const rapidjson::Value &a = shapeSpecs["center"];
		rapidjson::SizeType i = 0;
		float x = a[i].GetFloat();
		float y = a[i + 1].GetFloat();
		float z = a[i + 2].GetFloat();
		Vec3f center(x, y, z);

		float radius = shapeSpecs["radius"].GetFloat();

		Sphere *sphere = new Sphere();

		sphere->setCenter(center);
		sphere->setRadius(radius);

		rapidjson::Value &materialSpecs = shapeSpecs["material"];
		sphere->setMaterial(Material::createMaterial(materialSpecs));

		return sphere;
	}

	// Rectangle parallel to the XY plane
	else if (shapeType.compare("rectangleXY") == 0)
	{
		float x0 = shapeSpecs["x0"].GetFloat();
		float x1 = shapeSpecs["x1"].GetFloat();
		float y0 = shapeSpecs["y0"].GetFloat();
		float y1 = shapeSpecs["y1"].GetFloat();
		float z = shapeSpecs["z"].GetFloat();

		RectangleXY *rectangle = new RectangleXY();
		rectangle->setVariables(x0, x1, y0, y1, z);

		rapidjson::Value &materialSpecs = shapeSpecs["material"];
		rectangle->setMaterial(Material::createMaterial(materialSpecs));

		return rectangle;
	}

	// Triangle
	else if (shapeType.compare("triangle") == 0)
	{
		const rapidjson::Value &a = shapeSpecs["v1"];
		rapidjson::SizeType i = 0;
		float x = a[i].GetFloat();
		float y = a[i + 1].GetFloat();
		float z = a[i + 2].GetFloat();
		Vec3f v1(x, y, z);

		const rapidjson::Value &b = shapeSpecs["v2"];
		i = 0;
		x = b[i].GetFloat();
		y = b[i + 1].GetFloat();
		z = b[i + 2].GetFloat();
		Vec3f v2(x, y, z);

		const rapidjson::Value &c = shapeSpecs["v3"];
		i = 0;
		x = c[i].GetFloat();
		y = c[i + 1].GetFloat();
		z = c[i + 2].GetFloat();
		Vec3f v3(x, y, z);

		Triangle *triangle = new Triangle();

		if (shapeSpecs.HasMember("uv1"))
		{
			const rapidjson::Value &d = shapeSpecs["uv1"];
			i = 0;
			x = d[i].GetFloat();
			y = d[i + 1].GetFloat();
			Vec2f uv1(x, y);

			const rapidjson::Value &e = shapeSpecs["uv2"];
			i = 0;
			x = e[i].GetFloat();
			y = e[i + 1].GetFloat();
			Vec2f uv2(x, y);

			const rapidjson::Value &f = shapeSpecs["uv3"];
			i = 0;
			x = f[i].GetFloat();
			y = f[i + 1].GetFloat();
			Vec2f uv3(x, y);

			triangle->setUV(uv1, uv2, uv3);
		}

		triangle->setVertices(v1, v2, v3);
		rapidjson::Value &materialSpecs = shapeSpecs["material"];
		triangle->setMaterial(Material::createMaterial(materialSpecs));

		return triangle;
	}

	// Triangular mesh
	else if (shapeType.compare("triangleMesh") == 0)
	{

		const rapidjson::Value &a = shapeSpecs["faceindex"];
		int *faceindex = new int[a.Size()];
		rapidjson::SizeType i = 0, j = 0;
		for (i = 0; i < a.Size(); i++)
		{
			faceindex[i] = a[i].GetInt();
		}

		const rapidjson::Value &b = shapeSpecs["vertexindex"];
		int *vertexindex = new int[b.Size()];
		i = 0;
		for (i = 0; i < b.Size(); i++)
		{
			vertexindex[i] = b[i].GetInt();
		}

		const rapidjson::Value &c = shapeSpecs["vertices"];
		Vec3f *vertices = new Vec3f[c.Size()];
		i = 0;
		for (i = 0; i < c.Size(); i++)
		{
			const rapidjson::Value &v = c[i];
			vertices[i] = Vec3f(v[j].GetFloat(), v[j + 1].GetFloat(), v[j + 2].GetFloat());
		}

		TriangleMesh *trimesh = new TriangleMesh();
		trimesh->setParameters(a.Size(), faceindex, vertexindex, vertices);

		if (shapeSpecs.HasMember("texturemap"))
		{
			const rapidjson::Value &d = shapeSpecs["texturemap"];
			Vec2f *verticesUV = new Vec2f[d.Size()];
			i = 0;
			for (i = 0; i < d.Size(); i++)
			{
				const rapidjson::Value &v = d[i];
				verticesUV[i] = Vec2f(v[j].GetFloat(), v[j + 1].GetFloat());
			}
			trimesh->setUV(verticesUV);
		}

		rapidjson::Value &materialSpecs = shapeSpecs["material"];
		trimesh->setMaterial(Material::createMaterial(materialSpecs));
		return trimesh;
	}

	return 0;
}

} //namespace rt
