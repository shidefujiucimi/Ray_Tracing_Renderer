#ifndef MATRIAL_H
#define MATRIAL_H
#include <hittable.h>
#include <pdf.h>
class scatter_record {
public:
    glm::vec3 attenuation;
    shared_ptr<pdf> pdf_ptr;
    bool skip_pdf;
    Ray skip_pdf_ray;
};

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const {
        return false;
    }


    virtual glm::vec3 emitted(const glm::vec3& p, const Hit_record& rec) const {
        return glm::vec3(0, 0, 0);
    }
    virtual double scattering_pdf(const Ray& r_in, const Hit_record& rec, const Ray& scattered)
        const {
        return 0;
    }
};
class lambertian : public material {
public:
    lambertian(const glm::vec3& albedo);

    bool scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const override;
    double scattering_pdf(const Ray& r_in, const Hit_record& rec, const Ray& scattered) const override;
     
private:
    glm::vec3 albedo;
};
class metal : public material {
public:
    metal(const glm::vec3& albedo, float fuzz);

    bool scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec)const override;

private:
    glm::vec3 albedo;
    float fuzz;
};
class dielectric : public material {
public:
    dielectric(double refraction_index);

    bool scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const override;

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;

    static double reflectance(double cosine, double refraction_index);
};
class isotropic : public material {
public:
    isotropic(glm::vec3& albedo);

    bool scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const override;
    double scattering_pdf(const Ray& r_in, const Hit_record& rec, const Ray& scattered)const;

private:
    glm::vec3& albedo;
};
class diffuse_light : public material {
public:
    diffuse_light(glm::vec3 color);

    glm::vec3 emitted(const glm::vec3& p, const Hit_record& rec) const;

private:
    glm::vec3 color;
};
#endif

