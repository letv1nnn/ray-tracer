#pragma once

#include <cmath>
#include <ostream>

#include "types.hpp"
#include "utils.hpp"

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
    constexpr vec3 operator-() const noexcept {
        return vec3(-x, -y, -z);
    }
public: // other methods
    constexpr f64 length() const {
        return std::sqrt(length_squared());
    }
    constexpr f64 length_squared() const {
        return x * x + y * y + z * z;
    }
    constexpr bool near_zero() const {
        // return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
    }
public: // static methods
    static vec3 random() {
        return vec3{random_f64(), random_f64(), random_f64()};
    }
    static vec3 random(f64 min, f64 max) {
        return vec3{random_f64(min, max), random_f64(min, max), random_f64(min, max)};
    }
};

// vec3 utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}
constexpr vec3 operator+(const vec3& va, const vec3& vb) {
    return vec3(va.x + vb.x, va.y + vb.y, va.z + vb.z);
}
constexpr vec3 operator-(const vec3& va, const vec3& vb) {
    return vec3(va.x - vb.x, va.y - vb.y, va.z - vb.z);
}
constexpr vec3 operator*(const vec3& va, const vec3& vb) { // not a dot product
    return vec3(va.x * vb.x, va.y * vb.y, va.z * vb.z);
}
constexpr vec3 operator*(f64 scalar, const vec3& v) {
    return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}
constexpr vec3 operator*(const vec3& v, f64 scalar) {
    return scalar * v;
}
constexpr vec3 operator/(const vec3& v, double scalar) {
    return (scalar != 0) ? (1/scalar) * v : vec3{};
}
constexpr f64 dot(const vec3& va, const vec3& vb) {
    return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}
constexpr vec3 cross(const vec3& va, const vec3& vb) {
    return vec3(va.y * vb.z - va.z * vb.y, va.z * vb.x - va.x * vb.z, va.x * vb.y - va.y * vb.x);
}
constexpr vec3 unit(const vec3& v) {
    return v / v.length();
}
inline vec3 random_unit_vector() {
    while (1) {
        const auto p = vec3::random(-1, 1);
        const auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}
// function that would compare the random vector and the surface normal
// by checking whether the dot product is negative, then we need to invert the vector,
// otherwise, keep it as it is.
inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    // in the same hemisphere as the normal
    return (dot(on_unit_sphere, normal) > 0.0) ? on_unit_sphere : -on_unit_sphere;
}
constexpr vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

}
