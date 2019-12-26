/*
 * TriangleMesh.cpp
 *
 *
 */
#include "TriangleMesh.h"
#include "Triangle.h"

namespace rt
{

/**
	 * Computes whether a ray hit the specific instance of a TriangleMesh shape and finds the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 * 
	 * @param t_min and t_max are valid range of values for t. If t does not lie in the range, no intersection
	 *
	 * @param hit or intersection information
	 * 
	 * @return true if ray intersects with triangle mesh, false otherwise
	 *
	 */

bool TriangleMesh::hit(const Ray &r, float t_min, float t_max, Hit &rec) const
{
    int j = 0;
    bool isect = false;
    for (int i = 0; i < numTris; ++i)
    {
        const Vec3f &v0 = P[trisIndex[j]];
        const Vec3f &v1 = P[trisIndex[j + 1]];
        const Vec3f &v2 = P[trisIndex[j + 2]];

        Triangle *tri = new Triangle();
        tri->setVertices(v0, v1, v2);
        tri->setMaterial(this->getMaterial());
        tri->setUV(texCoordinates[trisIndex[j]], texCoordinates[trisIndex[j + 1]], texCoordinates[trisIndex[j + 2]]);
        float tNear = t_max;

        Hit rec1;
        if (tri->hit(r, t_min, t_max, rec1))
        {
            if (rec1.t < tNear)
            {
                tNear = rec1.t;
                isect = true;
                rec = rec1;
            }
        }
        j += 3;
    }

    return isect;
}

// Bounding box for the triangle mesh
bool TriangleMesh::bounding_box(aabb &box) const
{
    float _xmin = P[0].x;
    float _ymin = P[0].y;
    float _zmin = P[0].z;
    float _xmax = P[0].x;
    float _ymax = P[0].y;
    float _zmax = P[0].z;
    for (int i = 0; i < sizeof(P); i++)
    {
        if (P[i].x < _xmin)
            _xmin = P[i].x;
        if (P[i].y < _ymin)
            _ymin = P[i].y;
        if (P[i].z < _zmin)
            _zmin = P[i].z;

        if (P[i].x > _xmax)
            _ymax = P[i].x;
        if (P[i].y > _ymin)
            _ymax = P[i].y;
        if (P[i].z > _zmax)
            _zmax = P[i].z;
    }

    box = aabb(Vec3f(_xmin, _ymin, _zmin), Vec3f(_xmax, _ymax, _zmax));
    return true;
}

// Initialize the triangle mesh
void TriangleMesh::setParameters(int nfaces, int faceIndex[], int vertsIndex[], Vec3f verts[])
{
    int k = 0, maxVertIndex = 0;
    numTris = 0;

    // find out how many triangles we need to create for this mesh
    for (int i = 0; i < nfaces; ++i)
    {
        numTris += faceIndex[i] - 2;
        for (int j = 0; j < faceIndex[i]; ++j)
            if (vertsIndex[k + j] > maxVertIndex)
                maxVertIndex = vertsIndex[k + j];
        k += faceIndex[i];
    }
    maxVertIndex += 1;

    // allocate memory to store the position of the mesh vertices
    P = new Vec3f[maxVertIndex];
    for (int i = 0; i < maxVertIndex; ++i)
    {
        P[i] = verts[i];
    }

    // allocate memory to store triangle indices
    trisIndex = new int[numTris * 3];
    int l = 0;

    N = new Vec3f[numTris * 3];
    texCoordinates = new Vec2f[numTris * 3];
    for (int i = 0, k = 0; i < nfaces; ++i)
    { // for each  face
        for (int j = 0; j < faceIndex[i] - 2; ++j)
        { // for each triangle in the face
            trisIndex[l] = vertsIndex[k];
            trisIndex[l + 1] = vertsIndex[k + j + 1];
            trisIndex[l + 2] = vertsIndex[k + j + 2];
            l += 3;
        }
        k += faceIndex[i];
    }
}

void TriangleMesh::setUV(Vec2f vertsUV[])
{
    texCoordinates = new Vec2f[sizeof(P)];
    for (int i = 0; i < sizeof(P); ++i)
    {
        texCoordinates[i] = vertsUV[i];
    }
}

} //namespace rt
