#pragma once

#include "hittable.hpp"
#include "vec3.hpp"

namespace raytracer {

class material {
public: // constructors and destructors
    constexpr virtual ~material() = default;
public: // other methods
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return 0;
    }
};

class lambertian : public material {
private: // attributes
    color albedo; // how much ligh does a material reflect
public: // constructors and destructors
    constexpr lambertian(const color& albedo) : albedo{albedo} {}
public: // other methods
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // catch degenerate scatter direction
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray{rec.p, scatter_direction};
        attenuation = albedo;
        return 1;
    }
};

class metal : public material {
private: // attributes
    color albedo;
    f64 fuzz;
public: // constructors and destructors
    constexpr metal(const color& albedo, f64 fuzz) : albedo{albedo}, fuzz{fuzz < 1 ? fuzz : 1} {}
public: // other methods
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override {
        vec3 reflected = reflect(r_in.get_direction(), rec.normal);
        reflected = unit(reflected) + (fuzz * random_unit_vector());
        scattered = ray{rec.p, reflected};
        attenuation = albedo;
        return (dot(scattered.get_direction(), rec.normal) > 0);
    }

};

}
