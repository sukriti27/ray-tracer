/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"
#include "math/geometry.h"

namespace rt
{

class PointLight : public LightSource
{

  public:
	PointLight(){};

	~PointLight(){};

	void setPosition(Vec3f p) { position = p; }
	void setIntensity(Vec3f i) { intensity = i; }
	Vec3f getPosition() { return position; }
	Vec3f getIntensity() { return intensity; }

  private:
	Vec3f position;
	Vec3f intensity;
};

} //namespace rt

#endif /* POINTLIGHT_H_ */
