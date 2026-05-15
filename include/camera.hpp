#pragma once

#include "common.hpp"
#include "hittable.hpp"

namespace raytracer {

class camera {
private: // attributes
    f64 aspect_ratio;       // resolution ratio
    i32 image_width;        // render image width
    i32 image_height;       // render image height
    i32 samples_per_pixel;  // number of samples per pixel for antialiasing
    f64 pixel_samples_scale;// color scale factor for a sum of pixel samples
    vec3 center;            // camera center
    vec3 pixel00_loc;       // location of pixel (0, 0)
    vec3 pixel_delta_u;     // offset to pixel to the right
    vec3 pixel_delta_v;     // offset to pixel below
public: // constructors and destructors
    constexpr camera(f64 aspect_ratio = 1.0, i32 image_width = 100, i32 samples_per_pixel = 10) 
        : aspect_ratio{aspect_ratio}, image_width{image_width}, samples_per_pixel{samples_per_pixel} {}
public: // getters and setters
    constexpr f64 get_aspect_ratio() const noexcept { return aspect_ratio; }
    constexpr i32 get_image_width() const noexcept { return image_width; }
    constexpr i32 get_image_height() const noexcept { return image_height; }
    constexpr i32 get_samples_per_pixel() const noexcept { return samples_per_pixel; }
    constexpr i32 get_pixel_samples_scale() const noexcept { return pixel_samples_scale; }
    constexpr const vec3& get_center() const noexcept { return center; }
    constexpr const vec3& get_pixel00_loc() const noexcept { return pixel00_loc; }
    constexpr const vec3& get_pixel_delta_u() const noexcept { return pixel_delta_u; }
    constexpr const vec3& get_pixel_delta_v() const noexcept { return pixel_delta_v; }
private: // private helper methods
    void initialize() {
        // calculate the image height, and ensure that it's at least 1.
        image_height = std::max(1, static_cast<i32>(image_width / aspect_ratio));
        
        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = vec3{};

        // viewport dimensions
        const f64 focal_length{1.0}; // distance from the camera to the viewport.
        // viewport (virtual plane) widths less than one are ok since they are real valued.
        const f64 viewport_height{2.0};
        const f64 viewport_width = viewport_height * (static_cast<f64>(image_width) / image_height);

        // calculate the vectors across the horizontal and down the vertical viewport edges.
        const vec3 viewport_u{viewport_width, 0.0, 0.0}; // horizontal
        const vec3 viewport_v{0.0, -viewport_height, 0.0}; // vertical

        // calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // calculate the location of the upper left pixel.
        // the initial position is not (0, 0), since this is the center of the viewport.
        const vec3 viewport_upper_left = center - vec3{0.0, 0.0, focal_length} - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    color ray_color(const ray& r, const hittable& world) const {
        hit_record rec;
        if (world.hit(r, interval{0.0, infinity}, rec)) {
            return 0.5 * (rec.normal + raytracer::color{1.0, 1.0, 1.0});
        }

        const vec3 unit_direction = unit(r.get_direction());
        const f64 a = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
    }
    ray get_ray(i32 x, i32 y) {
        // construct a camera ray originating from the origin and directed at randomly smapled
        // point around the pixel location x, y.
        const auto offset = sample_square();
        const auto pixel_sample = pixel00_loc + ((x + offset.x) * pixel_delta_u) + ((y + offset.y) * pixel_delta_v);
        
        const auto ray_origin = center;
        const auto  ray_direction = pixel_sample - ray_origin;
    
        return ray(ray_origin, ray_direction);
    }
    inline vec3 sample_square() const {
        return vec3{random_f64() - 0.5, random_f64() - 0.5, 0.0};
    }
public: // other methods
    void render(const hittable& world) {
        initialize();
    
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (usize y{}; y < image_height; ++y) {
            std::clog << "\r Scanlines remaining: " << image_height - y << ' ' << std::flush;
            for (usize x{}; x < image_width; ++x) {
                color pixel_color{};
                for (i32 sample{}; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(x, y);
                    pixel_color += ray_color(r, world);
                }
                
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.\n";
    }
};

}

