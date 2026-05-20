#include <cstdlib>

#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"

int main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) {
   
    // world
    raytracer::hittable_list world;
    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{0, 0, -1}, 0.5));
    world.add(std::make_shared<raytracer::sphere>(raytracer::vec3{0, -100.5, -1}, 100));

    // camera
    raytracer::camera cam{16.0/9.0, 400, 100, 50};
    cam.render(world);

    return 0;
}

