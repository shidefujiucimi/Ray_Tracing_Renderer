#ifndef MATRIAL_H
#define MATRIAL_H
#include <hittable.h>

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(
        const Ray& r_in, const Hit_record& rec, glm::vec3& attenuation, Ray& scattered
    ) const {
        return false;
    }
};
class lambertian : public material {
public:
    lambertian(const glm::vec3& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const Hit_record& rec, glm::vec3& attenuation, Ray& scattered)
        const override {
        glm::vec3 scatter_direction = rec.normal + random_unit_vec3();

        // Catch degenerate scatter direction
        if (near_zero(scatter_direction))
            scatter_direction = rec.normal;

        scattered = Ray(rec.position, scatter_direction);
        attenuation = albedo;
        return true;
    }
     
private:
    glm::vec3 albedo;
};

class metal : public material {
public:
    metal(const glm::vec3& albedo,float fuzz) : albedo(albedo) ,fuzz(fuzz){}

    bool scatter(const Ray& r_in, const Hit_record& rec, glm::vec3& attenuation, Ray& scattered)
        const override {
        glm::vec3 reflected = glm::reflect(r_in.direction, rec.normal);
        reflected = normalize(reflected) + (fuzz * random_unit_vec3());//fuzz
        scattered = Ray(rec.position, reflected);
        attenuation = albedo;
        return (dot(scattered.direction, rec.normal) > 0);
    }

private:
    glm::vec3 albedo;
    float fuzz;
};
class dielectric : public material {
public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const Ray& r_in, const Hit_record& rec, glm::vec3& attenuation, Ray& scattered)
        const override {
        attenuation = glm::vec3(1.0, 1.0, 1.0);
        float ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
        glm::vec3 unit_direction = glm::normalize(r_in.direction);

        //When a ray enters a medium of lower index of refraction at a sufficiently glancing angle, 
        // it can not refract ,because the equality between the two sides of the equation is broken
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
        bool cannot_refract = ri * sin_theta > 1.0;
        glm::vec3 direction;
        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered = Ray(rec.position, direction);

        //glm::vec3 refracted = refract(unit_direction, rec.normal, ri);

        //scattered = Ray(rec.position, refracted);
        return true;
    }

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;

    static double reflectance(double cosine, double refraction_index) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};

#endif

