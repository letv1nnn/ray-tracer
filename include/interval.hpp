#pragma once

#include "common.hpp"

namespace raytracer {

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
};

}

