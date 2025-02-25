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

#endif

