#pragma once

#include "vec3.hpp"
#include "types.hpp"
#include "interval.hpp"

namespace raytracer {

using color = vec3;

// function to convert normilized color value or set to rgb (8 bits)
constexpr i32 to_rgb8(f64 value) {
    return static_cast<i32>(255.999 * value);
}
constexpr color to_rgb8(color normalized_color) {
    return color(to_rgb8(normalized_color.x), to_rgb8(normalized_color.y), to_rgb8(normalized_color.z));  
}

constexpr f64 linear_to_gamma(f64 linear_component) {
    return (linear_component > 0) ? std::sqrt(linear_component) : 0;
}

// write color to out
const auto write_color = [](std::ostream& out, color rgb8_color) -> void {
    const f64 r = linear_to_gamma(rgb8_color.x);    
    const f64 g = linear_to_gamma(rgb8_color.y);    
    const f64 b = linear_to_gamma(rgb8_color.z);    
    
    static const interval intensity{0.0, 0.999}; 
    i32 rbyte = static_cast<i32>(256 * intensity.clamp(r));
    i32 gbyte = static_cast<i32>(256 * intensity.clamp(g));
    i32 bbyte = static_cast<i32>(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
};

}
