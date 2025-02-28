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
class translate : public Hittable {
public:
	translate(shared_ptr<Hittable> object, const glm::vec3& offset)
		: object(object), offset(offset)
	{
		bbox = object->bounding_box() + offset;
	}

	bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override {
		// Move the ray backwards by the offset
		Ray offset_r(r.origin - offset, r.direction);

		// Determine whether an intersection exists along the offset ray (and if so, where)
		if (!object->hit(offset_r, ray_t, rec))
			return false;

		// Move the intersection point forwards by the offset
		rec.position += offset;

		return true;
	}
	aabb bounding_box() const override { return bbox; }
private:
	shared_ptr<Hittable> object;
	glm::vec3 offset;
	aabb bbox;
};
#endif
