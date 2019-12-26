/*
 * Transparent.h
 *
 *
 */

#ifndef TRANSPARENT_H_
#define TRANSPARENT_H_

#include "core/Material.h"
#include "math/geometry.h"

namespace rt
{

class Transparent : public Material
{

  public:
    Transparent(){};

    ~Transparent(){};

    void setParameters(float _refractiveIndex)
    {
        refractiveIndex = _refractiveIndex;
    };

    float getRefractiveIndex() { return refractiveIndex; };

  private:
    float refractiveIndex;
};

} //namespace rt

#endif /* TRANSPARENT_H_ */
