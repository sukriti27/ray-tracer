/*
 * TriangleMesh.h
 *
 *
 */

#ifndef TRIANGLEMESH_H_
#define TRIANGLEMESH_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"

namespace rt
{

class TriangleMesh : public Shape
{

  public:
    TriangleMesh() : Shape(){};
    ~TriangleMesh(){};

    bool hit(const Ray &r, float tmin, float tmax, Hit &rec) const;
    bool bounding_box(aabb &box) const;
    void setParameters(int nfaces, int faceIndex[], int vertsIndex[], Vec3f verts[]);
    void setUV(Vec2f vertsUV[]);

  private:
    int numTris = 0;       // number of triangles
    Vec3f *P;              // triangles vertex position
    int *trisIndex;        // vertex index array
    Vec3f *N;              // triangles vertex normals
    Vec2f *texCoordinates; // triangles texture coordinates
};

} //namespace rt

#endif /* TRIANGLEMESH_H_ */