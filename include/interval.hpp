#pragma once

#include "common.hpp"

namespace raytracer {

constexpr f64 infinity = std::numeric_limits<f64>::infinity();

class interval {
public: // attributes
    f64 min, max;
public: // static attributes
    static const interval empty, universe;
public: // constructors and destructors
    constexpr interval() : min{+infinity}, max{-infinity} {}
    constexpr interval(f64 min, f64 max) : min{min}, max{max} {}
public: // other methods
    constexpr f64 size() const { return max - min; }
    constexpr bool contains(f64 x) const { return min <= x && x <= max; }
    constexpr bool surrounds(f64 x) const { return min < x && x < max; }
    constexpr f64 clamp(f64 x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
};

}

