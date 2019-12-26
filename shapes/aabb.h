#ifndef AABBH
#define AABBH

#include "core/Shape.h"
#include "core/RayHitStructs.h"
#include "rapidjson/document.h"

namespace rt{

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class aabb {
    public:
        aabb() {}
        aabb(const Vec3f& a, const Vec3f& b) { _min = a; _max = b;}  

        Vec3f min() const {return _min; }
        Vec3f max() const {return _max; }

        bool hit(const Ray& r, float tmin, float tmax) const {
            for (int a = 0; a < 3; a++) {
                float t0 = ffmin((_min[a] - r.origin()[a]) / r.direction()[a],  
                                (_max[a] - r.origin()[a]) / r.direction()[a]);
                float t1 = ffmax((_min[a] - r.origin()[a]) / r.direction()[a],  
                                (_max[a] - r.origin()[a]) / r.direction()[a]);
                tmin = ffmax(t0, tmin);
                tmax = ffmin(t1, tmax);
                if (tmax <= tmin)
                    return false;
            }
            return true;
        }

        Vec3f _min;
        Vec3f _max;
};

}

#endif