#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

// Std includes
#include <iostream>
#include <cmath>

// Local includes
#include <util/image.hpp>
#include <util/vec.hpp>
#include <ray.hpp>

namespace raycaster {

struct sphere {
    vec::vec3 c;
    float32 r;
    sphere(const vec::vec3 center, const float32 radius) {
        c = center;
        r = radius;
    }
    sphere operator=(const sphere& s) {
        c = s.c;
        r = s.r;
        return sphere(c, r);
    }
    float32 hitsRay(const ray3d ray) {
        vec::vec3 oc = c - ray.orig;
        float32 a = vec::dot3(ray.dir, ray.dir);
        float32 b = vec::dot3(ray.dir, oc);
        float32 c = vec::dot3(oc, oc) - r * r;
        float32 delta = b * b - a * c;

        if (delta < 0) {
            return -1.0f;
        }
        else {
            return (b - std::sqrt(delta)) / a;
        }
    }
};
struct triangle {
    vec::vec3 a, b, c;
    triangle(const vec::vec3 ea, const vec::vec3 eb, const vec::vec3 ec) {
        a = ea;
        b = eb;
        c = ec;
    }
    triangle operator=(const triangle& t) {
        a = t.a;
        b = t.b;
        c = t.c;
        return triangle(a, b, c);
    }
    float32 hitsRay(const ray3d ray) {

    }
};

pixelRGB raycast(ray3d ray) {
    sphere s(vec::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    float32 t = s.hitsRay(ray);
    if (t > 0) {
        vec::vec3 unit = normalize3(ray.at(t) - s.c);
        vec::vec3 col = 0.5f * vec::vec3(unit.x + 1.0f, unit.y + 1.0f, unit.z + 1.0f);
        return pixelRGB(col.x * 255, col.y * 255, col.z * 255);
    }

    // Gradient background
    // vec::vec3 unit_direction = vec::normalize3(ray.dir);
    // vec::vec3 a = 0.5f * (unit_direction.y + 1.0f);
    // vec::vec3 col = (1.0f - a) * vec::vec3(1.0, 1.0, 1.0) + a * vec::vec3(0.5, 0.7, 1.0);
    // return pixelRGB(col.x * 255, col.y * 255, col.z * 255);

    // Grey background
    return pixelRGB(10, 10, 10);
}
pixelRGB getPixel(vec::vec3 camPos, vec::vec3 pixelPos) {
    return raycast(ray3d(camPos, pixelPos - camPos));
}

}

#endif