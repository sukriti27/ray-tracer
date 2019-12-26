/*
 * LightSource.cpp
 *
 */
#include "LightSource.h"
#include "rapidjson/document.h"
#include "lights/AreaLight.h"
#include "lights/PointLight.h"
#include "rapidjson/istreamwrapper.h"
#include "math/geometry.h"

namespace rt
{

LightSource *LightSource::createLight(rapidjson::Value &lightSpecs)
{
	// Check if light type is defined

	if (!lightSpecs.HasMember("type"))
	{
		std::cerr << "Light type not specified" << std::endl;
		exit(-1);
	}

	std::string lightType = lightSpecs["type"].GetString();

	// Point light
	if (lightType.compare("pointlight") == 0)
	{

		const rapidjson::Value &a = lightSpecs["position"];
		rapidjson::SizeType i = 0;
		float x = a[i].GetFloat();
		float y = a[i + 1].GetFloat();
		float z = a[i + 2].GetFloat();
		Vec3f position(x, y, z);

		const rapidjson::Value &b = lightSpecs["intensity"];
		i = 0;
		x = b[i].GetFloat();
		y = b[i + 1].GetFloat();
		z = b[i + 2].GetFloat();
		Vec3f intensity(x, y, z);

		PointLight *light = new PointLight();
		light->setPosition(position);
		light->setIntensity(intensity);
		light->setType(lightType);
		return light;
	}

	// Area light
	else if (lightType.compare("arealight") == 0)
	{
		const rapidjson::Value &a = lightSpecs["intensity"];
		rapidjson::SizeType i = 0;
		float x = a[i].GetFloat();
		float y = a[i + 1].GetFloat();
		float z = a[i + 2].GetFloat();
		Vec3f intensity(x, y, z);

		const rapidjson::Value &b = lightSpecs["direction"];
		i = 0;
		x = b[i].GetFloat();
		y = b[i + 1].GetFloat();
		z = b[i + 2].GetFloat();
		Vec3f direction(x, y, z);

		AreaLight *area = new AreaLight();
		area->setPatarmeters(lightSpecs["x0"].GetFloat(), lightSpecs["x1"].GetFloat(), lightSpecs["y0"].GetFloat(),
							 lightSpecs["y1"].GetFloat(), lightSpecs["z"].GetFloat(), intensity, direction);
		area->setType(lightType);
		return area;
	}

	return 0;
}

} //namespace rt
