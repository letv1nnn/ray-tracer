#pragma once

#include <cmath>
#include <ostream>

#include "types.hpp"

namespace raytracer {

class vec3 {
public: // attributes
    f64 x{}, y{}, z{};
public: // constructors
    constexpr vec3() = default;
    constexpr vec3(f64 x, f64 y, f64 z) : x{x}, y{y}, z{z} {}
public: // operators
    constexpr vec3& operator+=(const vec3& other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }
    constexpr vec3& operator*=(f64 scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }
    constexpr vec3& operator/=(f64 scalar) {
        if (scalar == 0.0) { x = 0.0; y = 0.0; z = 0.0; }
        else { x /= scalar; y /= scalar; z /= scalar; }
        return *this;
    }
public: // other methods
    constexpr f64 length() const {
        return std::sqrt(length_squared());
    }
    constexpr f64 length_squared() const {
        return x * x + y * y + z * z;
    }
};

// vec3 utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}
inline vec3 operator+(const vec3& va, const vec3& vb) {
    return vec3(va.x + vb.x, va.y + vb.y, va.z + vb.z);
}
inline vec3 operator-(const vec3& va, const vec3& vb) {
    return vec3(va.x - vb.x, va.y - vb.y, va.z - vb.z);
}
inline vec3 operator*(const vec3& va, const vec3& vb) { // not a dot product
    return vec3(va.x * vb.x, va.y * vb.y, va.z * vb.z);
}
inline vec3 operator*(f64 scalar, const vec3& v) {
    return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}
inline vec3 operator*(const vec3& v, f64 scalar) {
    return scalar * v;
}
inline vec3 operator/(const vec3& v, double scalar) {
    return (scalar != 0) ? (1/scalar) * v : vec3{};
}
inline f64 dot(const vec3& va, const vec3& vb) {
    return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}
inline vec3 cross(const vec3& va, const vec3& vb) {
    return vec3(va.y * vb.z - va.z * vb.y, va.z * vb.x - va.x * vb.z, va.x * vb.y - va.y * vb.x);
}
inline vec3 unit(const vec3& v) {
    return v / v.length();
}

}
