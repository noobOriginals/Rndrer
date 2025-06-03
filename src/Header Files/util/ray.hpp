#ifndef RAY_HPP
#define RAY_HPP

// Local includes
#include <util/vec.hpp>

struct ray3d {
    vec3 orig, dir;
    ray3d() {
        orig = dir = vec3(0.0f);
    }
    ray3d(const vec3 origin, const vec3 direction) {
        orig = origin;
        dir = direction;
    }
    vec3 at(const float32 t) {
        return orig + dir * t;
    }
    ray3d operator=(const ray3d& r) {
        return ray3d(r.orig, r.dir);
    }
};

#endif