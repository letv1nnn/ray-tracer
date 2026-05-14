#pragma once

#include "hittable.hpp"

#include <vector>

namespace raytracer {

class hittable_list : public hittable {
public: // attributes
    std::vector<std::shared_ptr<hittable>> objects;
public: // constructors and destructors
    constexpr hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) { add(object); }
public: // other methods
    constexpr void clear() { objects.clear(); }    
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
    bool hit(const ray &r, f64 ray_tmin, f64 ray_tmax, hit_record &rec) const override {
        hit_record temp_rec;
        bool hit_anything{};
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = 1;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    } 
};


}
