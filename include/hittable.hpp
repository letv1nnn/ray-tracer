#pragma once

#include "common.hpp"
#include "interval.hpp"

namespace raytracer {

struct hit_record {
// attributes
    vec3 p;
    vec3 normal;
    f64 t;
    bool front_face;
// other methods
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // sets the hit record normal vector
        front_face = dot(r.get_direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public: // constructors and destructors
    virtual ~hittable() = default;
public: // other methods
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

}
