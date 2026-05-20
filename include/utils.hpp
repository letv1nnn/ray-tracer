#pragma once

#include <random>
#include "types.hpp"

namespace raytracer {

constexpr f64 pi = 3.1415926535897932385;

constexpr f64 degrees_to_radians(f64 degrees) {
    return degrees * pi / 180.0;
}

inline f64 random_f64() {
    static std::uniform_real_distribution<f64> distribution(0.0, 1.0);
    static std::mt19937 generator;

    return distribution(generator);
}

inline f64 random_f64(f64 min, f64 max) {
    return min + (max - min) * random_f64();
}

}
