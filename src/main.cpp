#include <iostream>

#include "types.hpp"
#include "color.hpp"
#include "vec3.hpp"

constexpr usize image_width{256};
constexpr usize image_height{256};

constexpr i32 to_color(f64 value);

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) {
   
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (usize y{}; y < image_height; ++y) {
        for (usize x{}; x < image_width; ++x) {

            const raytracer::vec3 normilized_color(
                static_cast<f64>(x) / (image_width - 1),
                static_cast<f64>(y) / (image_height - 1),
                0.0
            );
            
            const raytracer::color rgb8 = raytracer::to_rgb8(normilized_color);
            
            raytracer::write_color(std::cout, rgb8);
        }
    }

    return 0;
}

