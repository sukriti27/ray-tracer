/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include "core/Material.h"
#include "math/geometry.h"
#include "Texture.h"

namespace rt
{

class BlinnPhong : public Material
{

  public:
    BlinnPhong(){};
    ~BlinnPhong(){};

    void setParameters(float _ks, float _kd, float _specularExponent);
    void setDiffuseColor(Vec3f _diffuseColor);
    void setTexture(Texture *t);
    Vec3f getTextureRGB(float u, float v);
    float getKs();
    float getKd();
    int getSpecularExponent();
    Vec3f getDiffuseColor();
    bool hasTextureValue();

  private:
    float ks;
    float kd;
    int specularExponent;
    Vec3f diffuseColor;
    Texture *texture;
    bool hasTexture;
};

} //namespace rt

#endif /* BLINNPHONG_H_ */
