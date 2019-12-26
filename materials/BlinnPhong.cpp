/*
 * BlinnPhong.cpp
 *
 *
 */

#include "BlinnPhong.h"

namespace rt
{

// Initialize the value of specular and diffuse components
void BlinnPhong::setParameters(float _ks, float _kd, float _specularExponent)
{
    ks = _ks;
    kd = _kd;
    specularExponent = _specularExponent;
};

// Set the diffuse color
void BlinnPhong::setDiffuseColor(Vec3f _diffuseColor)
{
    diffuseColor = _diffuseColor;
    hasTexture = false;
};

// Set texture
void BlinnPhong::setTexture(Texture *t)
{
    texture = t;
    hasTexture = true;
};

// Get RGB value of texture from UV coordinates
Vec3f BlinnPhong::getTextureRGB(float u, float v)
{
    return texture->getRGB(u, v);
};

// Get the value of specular component ks
float BlinnPhong::getKs() { return ks; };

// Get the value of diffuse component kd
float BlinnPhong::getKd() { return kd; };

// Get the value of specular exponent
int BlinnPhong::getSpecularExponent() { return specularExponent; };

// Get the diffuse color vectore
Vec3f BlinnPhong::getDiffuseColor() { return diffuseColor; };

// Check if the object has a texture
bool BlinnPhong::hasTextureValue() { return hasTexture; };

} //namespace rt
