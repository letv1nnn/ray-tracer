#pragma once

#include "ray.hpp"
#include "types.hpp"
#include "vec3.hpp"

namespace raytracer {

class hit_record {
public: // attributes
    vec3 p;
    vec3 normal;
    f64 t;
};

class hittable {
public: // constructors and destructors
    virtual ~hittable() = default;
public: // other methods
    virtual bool hit(const ray& r, f64 ray_tmin, f64 ray_tmax, hit_record& rec) const = 0;
};

}
