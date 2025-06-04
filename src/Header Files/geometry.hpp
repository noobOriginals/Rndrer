#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

// Local includes
#include <util/types.h>
#include <util/image.hpp>
#include <util/math.hpp>

namespace geo {

image::Pixel vecToPixel(math::Vec3 v) {
    return image::Pixel(255 * v.x, 255 * v.y, 255 * v.z);
}
struct Ray {
    math::Vec3 orig, dir;
    Ray() {
        orig = dir = math::Vec3(0.0f);
    }
    Ray(math::Vec3 origin, math::Vec3 direction) {
        orig = origin;
        dir = math::normalize(direction);
    }
    math::Vec3 at(const float32 t) {
        return orig + dir * t;
    }
    Ray& operator=(const Ray& r) {
        orig = r.orig;
        dir = r.dir;
        return *this;
    }
};
struct Sphere {
    math::Vec3 c;
    float32 r;
    Sphere(math::Vec3 center, float32 radius) {
        c = center;
        r = radius;
    }
    Sphere& operator=(const Sphere& s) {
        c = s.c;
        r = s.r;
        return *this;
    }
    float32 hitRay(Ray ray) {
        math::Vec3 oc = c - ray.orig;
        float32 a = ray.dir.lenSq();
        float32 b = math::dot(ray.dir, oc);
        float32 c = oc.lenSq() - r * r;
        float32 delta = b * b - a * c;
        if (delta < 0) {
            return -1.0f;
        }
        else {
            return (b - std::sqrt(delta)) / a;
        }
    }
};
struct Triangle {
    math::Vec3 a, b, c;
    Triangle(math::Vec3 aa, math::Vec3 ab, math::Vec3 ac) {
        a = aa;
        b = ab;
        c = ac;
    }
    Triangle& operator=(const Triangle& t) {
        a = t.a;
        b = t.b;
        c = t.c;
        return *this;
    }
};

}

#endif