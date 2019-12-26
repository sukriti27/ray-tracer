/*
 * Material.cpp
 *
 */
#include "Material.h"
#include "materials/BlinnPhong.h"
#include "materials/Reflective.h"
#include "materials/Transparent.h"
#include "rapidjson/document.h"

namespace rt
{

Material *Material::createMaterial(rapidjson::Value &materialSpecs)
{
    // Check if materual type is defined

    if (!materialSpecs.HasMember("type"))
    {
        std::cerr << "Material type not specified" << std::endl;
        exit(-1);
    }

    std::string materialType = materialSpecs["type"].GetString();
    if (materialType.compare("blinnphong") == 0)
    {
        BlinnPhong *phong = new BlinnPhong();

        if (!materialSpecs.HasMember("texture"))
        {
            const rapidjson::Value &a = materialSpecs["diffusecolor"];
            rapidjson::SizeType i = 0;
            float x = a[i].GetFloat();
            float y = a[i + 1].GetFloat();
            float z = a[i + 2].GetFloat();
            Vec3f diffuseColor = Vec3f(x, y, z);
            phong->setDiffuseColor(diffuseColor);
        }
        else
        {
            std::string location = materialSpecs["texture"].GetString();
            Texture *texture = new Texture();
            texture->setParameters(location);
            phong->setTexture(texture);
        }

        float ks = materialSpecs["ks"].GetFloat();
        float kd = materialSpecs["kd"].GetFloat();
        int specularExponent = materialSpecs["specularexponent"].GetInt();

        phong->setParameters(ks, kd, specularExponent);
        phong->setType(materialType);
        return phong;
    }
    else if (materialType.compare("reflective") == 0)
    {
        Reflective *ref = new Reflective();
        ref->setType(materialType);
        return ref;
    }
    else if (materialType.compare("transparent") == 0)
    {
        Transparent *tr = new Transparent();
        tr->setType(materialType);
        float refractiveIndex = materialSpecs["refractiveindex"].GetFloat();
        tr->setParameters(refractiveIndex);
        return tr;
    }
    else if (materialType.compare("texture") == 0)
    {
        Material *mat = new Material();
        mat->setType(materialType);
        return mat;
    }
    return 0;
}

} //namespace rt
