/*
 * Material.h
 *
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "rapidjson/document.h"

namespace rt
{

class Material
{
  public:
    virtual ~Material(){};
    static Material *createMaterial(rapidjson::Value &materialSpecs);
    void setType(std::string t) { type = t; }
    std::string getType() { return type; }

  private:
    std::string type;
};

} //namespace rt

#endif /* MATERIAL_H_ */
