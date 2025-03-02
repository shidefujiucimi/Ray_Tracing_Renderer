#ifndef PDF_H
#define PDF_H
#include <hittable.h>
#include <onb.h>
class pdf {
public:
    virtual ~pdf() {}

    virtual double value(const glm::vec3& direction) const = 0;
    virtual glm::vec3 generate() const = 0;
};
class sphere_pdf : public pdf {
public:
    sphere_pdf();

    double value(const glm::vec3& direction) const override;
    glm::vec3 generate() const override;
};
class cosine_pdf : public pdf {
public:
    cosine_pdf(const glm::vec3& w);

    double value(const glm::vec3& direction) const override;
    glm::vec3 generate() const override;
private:
    onb uvw;
};
class hittable_pdf : public pdf {
public:
    hittable_pdf(const Hittable& objects, const glm::vec3& origin);
     
    double value(const glm::vec3& direction) const override;
    glm::vec3 generate() const override;

private:
    const Hittable& objects;
    glm::vec3 origin;
};

#endif