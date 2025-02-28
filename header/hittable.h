#ifndef HITTABLE_H
#define HITTABLE_H
#include <common_header.h>
#include <interval.h>
#include <AABB.h>
class material;
class Hit_record {
public:
	glm::vec3 position;
	glm::vec3 normal;
	shared_ptr<material> mat;
	double t;
	bool front_face;
	Hit_record(){
		t = 0.0;
		front_face=false;
	}
	void set_face_normal(const Ray& r, const glm::vec3& outward_normal) {
		front_face = dot(r.direction, outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& r,interval ray_t, Hit_record& rec)const = 0;
	virtual aabb bounding_box() const = 0;
}; 
#endif
