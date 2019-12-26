/*
 * RectangleXY.h
 *
 *
 */

#ifndef RECTANGLEXY_H_
#define RECTANGLEXY_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"

namespace rt
{

class RectangleXY : public Shape
{

  public:
	RectangleXY() : Shape(){};

	~RectangleXY(){};

	//
	// Functions that need to be implemented, since Rectangle is a subclass of Shape
	//
	bool hit(const Ray &r, float tmin, float tmax, Hit &rec) const;
	bool bounding_box(aabb &box) const;
	void setVariables(float _x0, float _x1, float _y0, float _y1, float _k);

  private:
	float x0, x1, y0, y1, k;
};

} //namespace rt

#endif /* RECTANGLEXY_H_ */
