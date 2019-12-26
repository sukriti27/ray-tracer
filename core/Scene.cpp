/*
 * Scene.cpp
 *
 */
#include "Scene.h"
#include "rapidjson/document.h"

namespace rt
{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value &scenespecs)
{

	Value &shape = scenespecs["shapes"];
	SizeType i = 0;
	for (i = 0; i < shape.Size(); i++)
	{
		shapes.push_back(Shape::createShape(shape[i]));
	}

	Value &light = scenespecs["lightsources"];
	for (i = 0; i < light.Size(); i++)
	{
		lightSources.push_back(LightSource::createLight(light[i]));
	}

	Value &background = scenespecs["backgroundcolor"];
	i = 0;
	float x = background[i].GetFloat();
	float y = background[i + 1].GetFloat();
	float z = background[i + 2].GetFloat();
	backgroundColor = Vec3f(x, y, z);
}

} //namespace rt
