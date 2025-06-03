#ifndef VEC_HPP
#define VEC_HPP

// Std includes
#include <iostream>
#include <cmath>

// Local includes
#include <util/types.h>

struct vec3 {
    float32 e[3];
    float32& x = e[0];
    float32& y = e[1];
    float32& z = e[2];
    vec3() {
        e[0] = e[1] = e[2] = 0.0f;
    }
    vec3(const float32 f) {
        e[0] = e[1] = e[2] = f;
    }
    vec3(const float32 a, const float32 b, const float32 c) {
        e[0] = a;
        e[1] = b;
        e[2] = c;
    }
    vec3(const float32 v[3]) {
        e[0] = v[0];
        e[1] = v[1];
        e[2] = v[2];
    }
    float32 len() {
        return std::sqrt(x * x + y * y + z * z);
    }
    float32& operator[](const int32 i) {
        return e[i];
    }
    vec3 operator-() {
        return vec3(-e[0], -e[1], -e[2]);
    }
    vec3 operator=(const vec3& v) {
        return vec3(v.x, v.y, v.z);
    }
};
// Vec3 Operators
vec3 operator+(vec3 v0, vec3 v1) {
    return vec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}
vec3 operator-(vec3 v0, vec3 v1) {
    return -v1 + v0;
}
vec3 operator+(vec3 v, float32 f) {
    return vec3(v.x + f, v.y + f, v.z + f);
}
vec3 operator+(float32 f, vec3 v) {
    return v + f;
}
vec3 operator-(vec3 v, float32 f) {
    return -f + v;
}
vec3 operator-(float32 f, vec3 v) {
    return -v + f;
}
vec3 operator*(vec3 v, float32 f) {
    return vec3(v.x * f, v.y * f, v.z * f);
}
vec3 operator*(float32 f, vec3 v) {
    return v * f;
}
vec3 operator/(vec3 v, float32 f) {
    return vec3(v.x / f, v.y / f, v.z / f);
}
vec3 operator/(float32 f, vec3 v) {
    return vec3(f / v.x, f / v.y, f / v.z);
}
vec3 operator*(vec3 v0, vec3 v1) {
    return vec3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}
vec3 operator/(vec3 v0, vec3 v1) {
    return v0 * (1 / v1);
}
std::ostream& operator<<(std::ostream& os, vec3 v) {
    os << v.x << "\n" << v.y << "\n" << v.z;
    return os;
}
// Other vec3 operators
float32 dot3(vec3 v0, vec3 v1) {
    return v0.x * v1.x + v0.y + v1.y + v0.z * v1.z;
}
vec3 cross3(vec3 v0, vec3 v1) {
    vec3 vec;
    vec.x = v0.y * v1.z - v0.z * v1.y;
    vec.y = v0.z * v1.x - v0.x * v1.z;
    vec.z = v0.x * v1.y - v0.y * v1.x;
    return vec;
}
vec3 normalize3(vec3 v) {
    return v / v.len();
}

#endif