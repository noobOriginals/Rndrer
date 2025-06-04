#ifndef MATH_HPP
#define MATH_HPP

// Std includes
#include <iostream>
#include <cmath>

// Local includes
#include <util/types.h>

namespace math {

// Vec3
struct Vec3 {
    float32 e[3];
    float32& x = e[0];
    float32& y = e[1];
    float32& z = e[2];
    Vec3() {
        e[0] = e[1] = e[2] = 0.0f;
    }
    Vec3(const float32 f) {
        e[0] = e[1] = e[2] = f;
    }
    Vec3(const float32 a, const float32 b, const float32 c) {
        e[0] = a;
        e[1] = b;
        e[2] = c;
    }
    Vec3(const float32 v[3]) {
        e[0] = v[0];
        e[1] = v[1];
        e[2] = v[2];
    }
    float32& operator[](const int32 i) {
        return e[i];
    }
    Vec3 operator-() {
        return Vec3(-e[0], -e[1], -e[2]);
    }
    Vec3& operator=(const Vec3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    float32 len() {
        return std::sqrt(x * x + y * y + z * z);
    }
    float32 lenSq() {
        return x * x + y * y + z * z;
    }
};
// Vec3 Operators
Vec3 operator+(Vec3 v0, Vec3 v1) {
    return Vec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}
Vec3 operator-(Vec3 v0, Vec3 v1) {
    return -v1 + v0;
}
Vec3 operator*(Vec3 v0, Vec3 v1) {
    return Vec3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}
Vec3 operator/(Vec3 v0, Vec3 v1) {
    return Vec3(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}
Vec3 operator+(Vec3 v, float32 f) {
    return Vec3(v.x + f, v.y + f, v.z + f);
}
Vec3 operator+(float32 f, Vec3 v) {
    return v + f;
}
Vec3 operator-(Vec3 v, float32 f) {
    return -f + v;
}
Vec3 operator-(float32 f, Vec3 v) {
    return -v + f;
}
Vec3 operator*(Vec3 v, float32 f) {
    return Vec3(v.x * f, v.y * f, v.z * f);
}
Vec3 operator*(float32 f, Vec3 v) {
    return v * f;
}
Vec3 operator/(Vec3 v, float32 f) {
    return Vec3(v.x / f, v.y / f, v.z / f);
}
Vec3 operator/(float32 f, Vec3 v) {
    return Vec3(f / v.x, f / v.y, f / v.z);
}
std::ostream& operator<<(std::ostream& os, Vec3 v) {
    os << v.x << "\n" << v.y << "\n" << v.z;
    return os;
}
// Other Vec3 operations
float32 dot(Vec3 v0, Vec3 v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}
Vec3 cross(Vec3 v0, Vec3 v1) {
    float32 x = v0.y * v1.z - v0.z * v1.y;
    float32 y = v0.z * v1.x - v0.x * v1.z;
    float32 z = v0.x * v1.y - v0.y * v1.x;
    return Vec3(x, y, z);
}
Vec3 normalize(Vec3 v) {
    return v / v.len();
}

}

#endif