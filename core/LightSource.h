/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include <vector>

#include "rapidjson/document.h"
#include "math/geometry.h"

namespace rt
{

class LightSource
{
  public:
	virtual ~LightSource(){};
	static LightSource *createLight(rapidjson::Value &lightSpecs);
	void setType(std::string t) { type = t; }
	std::string getType() { return type; }

  private:
	std::string type;
};

} //namespace rt

#endif /* LIGHTSOURCE_H_ */
