#include <iostream>

#include "types.hpp"

constexpr usize image_width{256};
constexpr usize image_height{256};

constexpr i32 to_color(f64 value);

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) {
   
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (usize y{}; y < image_height; ++y) {
        for (usize x{}; x < image_width; ++x) {
            const f64 r = static_cast<f64>(x) / (image_width - 1);
            const f64 g = static_cast<f64>(y) / (image_height - 1);
            const f64 b = 0.0;

            std::cout << to_color(r) << ' ' << to_color(g) << ' ' << to_color(b) << '\n';
        }
    }

    return 0;
}

constexpr i32 to_color(f64 value) {
    return static_cast<i32>(255.999 * value);
}

