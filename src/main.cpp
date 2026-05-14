#include <cstdlib>

#include "color.hpp"
#include "common.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

raytracer::color ray_color(const raytracer::ray& r, const raytracer::hittable& world) {
    raytracer::hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + raytracer::color{1.0, 1.0, 1.0});
    }

    const raytracer::vec3 unit_direction = raytracer::unit(r.get_direction());
    const f64 a = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - a) * raytracer::color{1.0, 1.0, 1.0} + a * raytracer::color{0.5, 0.7, 1.0};
}

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) {
   
    constexpr f64 aspect_ratio = 16.0 / 9.0;
    constexpr usize image_width{400}; 
    
    // calculate the image height, and ensure that it's at least 1.
    constexpr i32 image_height = std::max(1, static_cast<i32>(image_width / aspect_ratio)); 

    // world
    raytracer::hittable_list world;
    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{0, 0, -1}, 0.5));
    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{0, -100.5, -1}, 100));

    // camera
    constexpr f64 focal_length{1.0}; // distance from the camera to the viewport.
    // viewport (virtual plane) widths less than one are ok since they are real valued.
    constexpr f64 viewport_height{2.0};
    constexpr f64 viewport_width = viewport_height * (static_cast<f64>(image_width) / image_height);
    constexpr raytracer::vec3 camera_center{};

    // calculate the vectors across the horizontal and down the vertical viewport edges.
    constexpr raytracer::vec3 viewport_u{viewport_width, 0.0, 0.0}; // horizontal
    constexpr raytracer::vec3 viewport_v{0.0, -viewport_height, 0.0}; // vertical

    // calculate the horizontal and vertical delta vectors from pixel to pixel.
    const raytracer::vec3 pixel_delta_u = viewport_u / image_width;
    const raytracer::vec3 pixel_delta_v = viewport_v / image_height;

    // calculate the location of the upper left pixel.
    // the initial position is not (0, 0), since this is the center of the viewport.
    const raytracer::vec3 viewport_upper_left = camera_center - raytracer::vec3(0.0, 0.0, focal_length) - viewport_u / 2 - viewport_v / 2;
    const raytracer::vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // rendering
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (usize y{}; y < image_height; ++y) {
        std::clog << "\r Scanlines remaining: " << image_height - y << ' ' << std::flush;
        for (usize x{}; x < image_width; ++x) {

            const raytracer::vec3 pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
            const raytracer::vec3 ray_direction = pixel_center - camera_center;
            const raytracer::ray r(camera_center, ray_direction);

            const raytracer::color pixel_color = raytracer::to_rgb8(ray_color(r, world));
            raytracer::write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.\n";
    
    return 0;
}

