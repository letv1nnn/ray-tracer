#pragma once

#include "hittable.hpp"
#include "interval.hpp"

namespace raytracer {

class sphere : public hittable {
private: // attributes
    vec3 center;
    f64 radius;
    std::shared_ptr<material> mat;
public: // constructor
    constexpr sphere(const vec3& center, f64 radius) : center{center}, radius{std::fmax(0.0, radius)} {
        // TODO: Initialize the material pointer `mat`.
    }
public: // other methods
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
        const raytracer::vec3 oc = center - r.get_origin();
        const f64 a = r.get_direction().length_squared();
        const f64 h = raytracer::dot(r.get_direction(), oc);
        const f64 c = oc.length_squared() - radius * radius;
        
        const f64 discriminant = h * h - a * c;
        if (discriminant < 0.0) return 0;
        
        const f64 sqrtd = std::sqrt(discriminant);

        // find the nearest root that lies the acceptable range.
        f64 root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) return 0;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        const vec3 outward = (rec.p - center) / radius;  // dividing by radius to normilize, since
        rec.set_face_normal(r, outward); // set_face_normal takes normilized normal
        rec.mat = mat;

        return 1;
    }
};

}
