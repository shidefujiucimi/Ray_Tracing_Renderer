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
        glm::vec3 reflected = reflect(r_in.direction, rec.normal);
        reflected = normalize(reflected) + (fuzz * random_unit_vec3());//fuzz
        scattered = Ray(rec.position, reflected);
        attenuation = albedo;
        return (dot(scattered.direction, rec.normal) > 0);
    }

private:
    glm::vec3 albedo;
    float fuzz;
};
#endif

