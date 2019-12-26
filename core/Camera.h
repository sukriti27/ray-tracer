/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "rapidjson/document.h"
#include "core/RayHitStructs.h"

using namespace rapidjson;

namespace rt
{

class Camera
{
  public:
	Camera(){};
	Camera(int height, int width, int fov) : height(height), width(width), fov(fov){};

	virtual ~Camera();

	static Camera *createCamera(Value &cameraSpecs);

	virtual void printCamera() = 0;

	virtual Ray get_ray(float u, float v) = 0;

	int getHeight() const
	{
		return height;
	}

	void setHeight(int h)
	{
		height = h;
	}

	int getWidth() const
	{
		return width;
	}

	void setWidth(int w)
	{
		width = w;
	}

  protected:
	int height;
	int width;
	int fov; //field of view
};

} //namespace rt

#endif /* CAMERA_H_ */
