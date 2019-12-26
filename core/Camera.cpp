/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"

namespace rt
{

Camera::~Camera(){};

/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera *Camera::createCamera(Value &cameraSpecs)
{

	//check if cameratype is defined

	if (!cameraSpecs.HasMember("type"))
	{
		std::cerr << "Camera type not specified" << std::endl;
		exit(-1);
	}

	std::string cameraType = cameraSpecs["type"].GetString();

	//return camera object based on camera specs
	if (cameraType.compare("pinhole") == 0)
	{
		Pinhole *pinhole = new Pinhole(cameraSpecs["width"].GetInt(),
									   cameraSpecs["height"].GetInt(),
									   cameraSpecs["fov"].GetInt());

		const rapidjson::Value &a = cameraSpecs["lookfrom"];
		rapidjson::SizeType i = 0;
		float x = a[i].GetFloat();
		float y = a[i + 1].GetFloat();
		float z = a[i + 2].GetFloat();
		Vec3f lookfrom(x, y, z);

		const rapidjson::Value &b = cameraSpecs["lookat"];
		i = 0;
		x = b[i].GetFloat();
		y = b[i + 1].GetFloat();
		z = b[i + 2].GetFloat();
		Vec3f lookat(x, y, z);

		const rapidjson::Value &c = cameraSpecs["vup"];
		i = 0;
		x = c[i].GetFloat();
		y = c[i + 1].GetFloat();
		z = c[i + 2].GetFloat();
		Vec3f vup(x, y, z);

		pinhole->setParameters(lookfrom, lookat, vup);
		return pinhole;
	}
	else if (cameraType.compare("thinlens") == 0)
	{
		ThinLens *thinlens = new ThinLens(cameraSpecs["width"].GetInt(),
										  cameraSpecs["height"].GetInt(),
										  cameraSpecs["fov"].GetInt());

		const rapidjson::Value &a = cameraSpecs["lookfrom"];
		rapidjson::SizeType i = 0;
		float x = a[i].GetFloat();
		float y = a[i + 1].GetFloat();
		float z = a[i + 2].GetFloat();
		Vec3f lookfrom(x, y, z);

		const rapidjson::Value &b = cameraSpecs["lookat"];
		i = 0;
		x = b[i].GetFloat();
		y = b[i + 1].GetFloat();
		z = b[i + 2].GetFloat();
		Vec3f lookat(x, y, z);

		const rapidjson::Value &c = cameraSpecs["vup"];
		i = 0;
		x = c[i].GetFloat();
		y = c[i + 1].GetFloat();
		z = c[i + 2].GetFloat();
		Vec3f vup(x, y, z);

		thinlens->setParameters(lookfrom, lookat, vup, cameraSpecs["aperture"].GetFloat(), cameraSpecs["focusdistance"].GetFloat());
		return thinlens;
	}

	return 0;
}

} //namespace rt
