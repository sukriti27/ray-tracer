/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "rapidjson/document.h"
#include "core/RayHitStructs.h"
#include "core/Material.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "shapes/aabb.h"

namespace rt
{

class Shape
{
  public:
	virtual ~Shape(){};

	static Shape *createShape(rapidjson::Value &shapeSpecs);

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual bool hit(const Ray &r, float t_min, float t_max, Hit &rec) const = 0;
	virtual bool bounding_box(aabb &box) const = 0;

	void setMaterial(Material *mat) { material = mat; }
	Material *getMaterial() const { return material; }

  protected:
	Material *material;
};

} //namespace rt

#endif /* SHAPE_H_ */
