/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"
#include <cstdlib>

namespace rt
{

class AreaLight : public LightSource
{

  public:
    AreaLight(){};

    ~AreaLight(){};

    // Initialize the fields for the rectangular area light
    void setPatarmeters(float _x0, float _x1, float _y0, float _y1, float _z, Vec3f _intensity, Vec3f _direction)
    {
        x0 = _x0;
        x1 = _x1;
        y0 = _y0;
        y1 = _y1;
        z = _z;
        intensity = _intensity;
        direction = _direction;
    }

    // Get a random point of the area light
    Vec3f getRandomPoint()
    {
        Vec3f point(x0 + (x1 - x0) * (rand() / (RAND_MAX + 1.0)), y0 + (y1 - y0) * (rand() / (RAND_MAX + 1.0)), z);
        return point;
    }

    Vec3f getIntensity() { return intensity; }
    Vec3f getDirection() { return direction; }

  private:
    float x0, x1, y0, y1, z;
    Vec3f intensity;
    Vec3f direction;
};

} //namespace rt

#endif /* AREALIGHT_H_ */
