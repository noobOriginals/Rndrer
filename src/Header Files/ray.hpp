#ifndef RAY_HPP
#define RAY_HPP

// Local includes
#include <util/vec.hpp>

struct ray3d {
    vec::vec3 orig, dir;
    ray3d() {
        orig = dir = vec::vec3(0.0f);
    }
    ray3d(vec::vec3 origin, vec::vec3 direction) {
        orig = origin;
        dir = direction;
    }
    vec::vec3 at(const float32 t) {
        return orig + dir * t;
    }
    ray3d operator=(const ray3d& r) {
        orig = r.orig;
        dir = r.dir;
        return ray3d(orig, dir);
    }
};

#endif