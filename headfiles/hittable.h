#ifndef HITTABLE_H
#define HITTABLE_H
#include <ray.h>
class Hit_record {
public:
	glm::vec3 position;
	glm::vec3 normal;
	double t;
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec)const = 0;
}; 
#endif
