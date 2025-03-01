#ifndef PDF_H
#define PDF_H
#include <hittable_list.h>
#include <onb.h>
class pdf {
public:
    virtual ~pdf() {}

    virtual double value(const glm::vec3& direction) const = 0;
    virtual glm::vec3 generate() const = 0;
};
class sphere_pdf : public pdf {
public:
    sphere_pdf() {}

    double value(const glm::vec3& direction) const override {
        return 1 / (4 * pi);
    }

    glm::vec3 generate() const override {
        return random_unit_vec3();
    }
};
class cosine_pdf : public pdf {
public:
    cosine_pdf(const glm::vec3& w) : uvw(w) {}

    double value(const glm::vec3& direction) const override {
        auto cosine_theta = dot(normalize(direction), uvw.w());
        return std::fmax(0, cosine_theta / pi);
    }

    glm::vec3 generate() const override {
        return uvw.transform(random_cosine_direction());
    }

private:
    onb uvw;
};
class hittable_pdf : public pdf {
public:
    hittable_pdf(const Hittable& objects, const glm::vec3& origin)
        : objects(objects), origin(origin)
    {}

    double value(const glm::vec3& direction) const override {
        return objects.pdf_value(origin, direction);
    }

    glm::vec3 generate() const override {
        return objects.random(origin);
    }

private:
    const Hittable& objects;
    glm::vec3 origin;
};
#endif