#pragma once

#include "vec3.hpp"

namespace raytracer {

class ray {
private: // attributes
    vec3 origin;
    vec3 direction;
public: // constructors
    constexpr ray() = default;
    constexpr ray(const vec3& origin, const vec3& direction) : origin{origin}, direction{direction} {}
public: // getters and setters
    constexpr const vec3& get_origin() const { return origin; }
    constexpr const vec3& get_direction() const { return direction; }
public: // other methods
    constexpr vec3 at(f64 t) const {
        return origin + t * direction; // P(t) = A + tb
    }
};

}

