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
struct HitPoint {
    math::Vec3 point;
    math::Vec3 normal;
    float32 t;
    bool frontFace;
    void setFaceNormal(Ray ray, math::Vec3 outwardNormal) {
        frontFace = math::dot(ray.dir, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
    HitPoint& operator=(const HitPoint& hp) {
        point = hp.point;
        normal = hp.normal;
        t = hp.t;
        frontFace = hp.frontFace;
        return *this;
    }
};
struct Hittable {
    virtual bool hitRay(Ray ray, float32 rayMin, float32 rayMax, HitPoint* p) = 0;
    virtual ~Hittable() {}
};
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
struct Sphere : Hittable {
    math::Vec3 c;
    float32 r;
    Sphere(math::Vec3 center, float32 radius) {
        c = center;
        r = (radius > 0) ? radius : 0.0f; // Ensure radius is positive
    }
    Sphere& operator=(const Sphere& s) {
        c = s.c;
        r = s.r;
        return *this;
    }
    bool hitRay(Ray ray, float32 rayMin, float32 rayMax, HitPoint* p) override {
        math::Vec3 oc = ray.orig - c;
        float32 a = ray.dir.lenSq();
        float32 h = math::dot(ray.dir, oc);
        float32 c = oc.lenSq() - r * r;
        float32 delta = h * h - a * c;
        if (delta < 0) {
            return false;
        }

        delta = std::sqrt(delta);
        float32 root = (h - delta) / a;
        if (root <= rayMin || root >= rayMax) {
            root = (h + delta) / a;
            if (root <= rayMin || root >= rayMax) {
                return false;
            }
        }

        p->t = root;
        p->point = ray.at(p->t);
        math::Vec3 normal = (p->point - c) / r;
        p->setFaceNormal(ray, normal);

        return true;
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