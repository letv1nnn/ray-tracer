#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>

#include "types.hpp"

namespace raytracer {

class vec3 {
public: // attributes
    f64 x{}, y{}, z{};
public: // constructors
    constexpr vec3() = default;
    constexpr vec3(f64 x, f64 y, f64 z);
public: // operators
    constexpr vec3& operator+=(const vec3& other);
    constexpr vec3& operator*=(f64 scalar);
    constexpr vec3& operator/=(f64 scalar);
public: // other methods
    constexpr f64 length() const;
    constexpr f64 length_squared() const;
};

// vec3 utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v);
inline vec3 operator+(const vec3& va, const vec3& vb);
inline vec3 operator-(const vec3& va, const vec3& vb);
inline vec3 operator*(const vec3& va, const vec3& vb);
inline vec3 operator*(f64 scalar, const vec3& v);
inline vec3 operator*(const vec3& v, f64 scalar);
inline vec3 operator/(const vec3& v, double scalar);
inline f64 dot(const vec3& va, const vec3& vb);
inline vec3 cross(const vec3& va, const vec3& vb);
inline vec3 unit(const vec3& v);
}
