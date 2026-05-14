#pragma once

#include "common.hpp"
#include "hittable.hpp"

namespace raytracer {

class camera {
private: // attributes
    f64 aspect_ratio{1.0};
    i32 image_width{100};

    i32 image_height;   // render image height
    vec3 center;        // camera center
    vec3 pixel00_loc;   // location of pixel (0, 0)
    vec3 pixel_delta_u; // offset to pixel to the right
    vec3 pixel_delta_v; // offset to pixel below
public: // constructors and destructors

private: // private helper methods
    void initialize() {
        // calculate the image height, and ensure that it's at least 1.
        image_height = std::max(1, static_cast<i32>(image_width / aspect_ratio));

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
        if (world.hit(r, interval{0, infinity}, rec)) {
            return 0.5 * (rec.normal + raytracer::color{1.0, 1.0, 1.0});
        }

        const vec3 unit_direction = unit(r.get_direction());
        const f64 a = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - a) * color{1.0, 1.0, 1.0} + a * color{0.5, 0.7, 1.0};
    }
public: // other methods
    void render(const hittable& world) {
        initialize();
    
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (usize y{}; y < image_height; ++y) {
            std::clog << "\r Scanlines remaining: " << image_height - y << ' ' << std::flush;
            for (usize x{}; x < image_width; ++x) {

                const vec3 pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
                const vec3 ray_direction = pixel_center - center;
                const ray r{center, ray_direction};

                const color pixel_color = to_rgb8(ray_color(r, world));
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.\n";
    }
};

}

