#ifndef RAY_HPP
#define RAY_HPP

// Local includes
#include <util/math.hpp>

struct Ray {
    math::Vec3 orig, dir;
    Ray() {
        orig = dir = math::Vec3(0.0f);
    }
    Ray(math::Vec3 origin, math::Vec3 direction) {
        orig = origin;
        dir = direction;
    }
    math::Vec3 at(const float32 t) {
        return orig + dir * t;
    }
    Ray operator=(const Ray& r) {
        orig = r.orig;
        dir = r.dir;
        return *this;
    }
};

#endif