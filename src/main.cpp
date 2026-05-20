#include <cstdlib>

#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) {
   
    // world
    raytracer::hittable_list world;

    const auto material_ground = std::make_shared<raytracer::lambertian>(raytracer::color{0.8, 0.8, 0.0});
    const auto material_center = std::make_shared<raytracer::lambertian>(raytracer::color{0.1, 0.2, 0.5});
    const auto material_left = std::make_shared<raytracer::metal>(raytracer::color{0.8, 0.8, 0.8}, 0.2);
    const auto material_right = std::make_shared<raytracer::metal>(raytracer::color{0.8, 0.6, 0.2}, 0.8);

    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{0.0, -100.5, -1.0}, 100, material_ground));
    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{0.0, 0.0, -1.2}, 0.5, material_center));
    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{-1.0, 0.0, -1.0}, 0.5, material_left));
    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{1.0, 0.0, -1.0}, 0.5, material_right));

    // camera
    raytracer::camera cam{16.0/9.0, 400, 100, 50};
    cam.render(world);

    return 0;
}

