#ifndef HITTABLE_H
#define HITTABLE_H
#include <ray.h>
class Hit_record {
public:
	glm::vec3 position;
	glm::vec3 normal;
	double t;
	bool front_face;

	void set_face_normal(const Ray& r, const glm::vec3& outward_normal) {
		front_face = dot(r.Direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec)const = 0;
}; 
#endif
