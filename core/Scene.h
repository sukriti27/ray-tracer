/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
#include "core/Shape.h"

using namespace rapidjson;

namespace rt
{

class Scene
{
  public:
	Scene(){};

	void createScene(Value &scenespecs);
	std::vector<Shape *> getShapes()
	{
		return shapes;
	};
	std::vector<LightSource *> getLights()
	{
		return lightSources;
	};
	Vec3f getBackgroundColor()
	{
		return backgroundColor;
	}

  private:
	std::vector<LightSource *> lightSources;
	std::vector<Shape *> shapes;
	Vec3f backgroundColor;
};

} //namespace rt

#endif /* SCENE_H_ */
