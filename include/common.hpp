#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// common headers
#include "types.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "color.hpp"

// constants
constexpr f64 infinity = std::numeric_limits<f64>::infinity();
constexpr f64 pi = 3.1415926535897932385;

// utility functions
constexpr f64 degrees_to_radians(f64 degrees) {
    return degrees * pi / 180.0;
}

