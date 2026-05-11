#pragma once

#include "vec3.hpp"
#include <ostream>

namespace raytracer {

using color = vec3;

// function to convert normilized color value or set to rgb (8 bits)
constexpr i32 to_rgb8(f64 value) {
    return static_cast<i32>(255.999 * value);
}
constexpr color to_rgb8(color normalized_color) {
    return color(to_rgb8(normalized_color.x), to_rgb8(normalized_color.y), to_rgb8(normalized_color.z));  
}

// write color to out
void write_color(std::ostream& out, color rgb8_color) {
    out << rgb8_color.x << ' ' << rgb8_color.y << ' ' << rgb8_color.z << '\n';
}

}
