#include <matrial.h>
lambertian::lambertian(const glm::vec3& albedo) : albedo(albedo) {}
bool lambertian::scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const{
    srec.attenuation = albedo;
    srec.pdf_ptr = make_shared<cosine_pdf>(rec.normal);
    srec.skip_pdf = false;
    return true;
}
double lambertian::scattering_pdf(const Ray& r_in, const Hit_record& rec, const Ray& scattered) const {
    auto cos_theta = dot(rec.normal, normalize(scattered.direction));
    return cos_theta < 0 ? 0 : cos_theta / pi;
}

metal::metal(const glm::vec3& albedo, float fuzz) : albedo(albedo), fuzz(fuzz) {}
bool metal::scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const {
    glm::vec3 reflected = glm::reflect(r_in.direction, rec.normal);
    reflected = normalize(reflected) + (fuzz * random_unit_vec3());//fuzz
    srec.attenuation = albedo;
    srec.pdf_ptr = nullptr;
    srec.skip_pdf = true;
    srec.skip_pdf_ray = Ray(rec.position, reflected);

    return true;
}

dielectric::dielectric(double refraction_index) : refraction_index(refraction_index) {}
bool dielectric::scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const{
    srec.attenuation = glm::vec3(1.0, 1.0, 1.0);
    srec.pdf_ptr = nullptr;
    srec.skip_pdf = true;
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

    srec.skip_pdf_ray = Ray(rec.position, direction);
    
    return true;
}
double dielectric::reflectance(double cosine, double refraction_index) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

diffuse_light::diffuse_light(glm::vec3 color) :color(color) {}
glm::vec3 diffuse_light::emitted(const glm::vec3& p, const Hit_record& rec) const{
    if (!rec.front_face)
        return glm::vec3(0);
    return color;
}

isotropic::isotropic(glm::vec3& albedo) : albedo(albedo) {}
bool isotropic::scatter(const Ray& r_in, const Hit_record& rec, scatter_record& srec) const{
    srec.attenuation = albedo;
    srec.pdf_ptr = make_shared<sphere_pdf>();
    srec.skip_pdf = false;
    return true;
}
double isotropic::scattering_pdf(const Ray& r_in, const Hit_record& rec, const Ray& scattered)const{
    return 1 / (4 * pi);
}