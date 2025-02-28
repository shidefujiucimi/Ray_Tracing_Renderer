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

class rotate_y : public Hittable {
public:
	rotate_y(shared_ptr<Hittable> object, double angle) : object(object) {
		auto radians = degrees_to_radians(angle);
		sin_theta = std::sin(radians);
		cos_theta = std::cos(radians);
		bbox = object->bounding_box();

		glm::vec3 min(infinity, infinity, infinity);
		glm::vec3 max(-infinity, -infinity, -infinity);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					auto x = i * bbox.x.max + (1 - i) * bbox.x.min;
					auto y = j * bbox.y.max + (1 - j) * bbox.y.min;
					auto z = k * bbox.z.max + (1 - k) * bbox.z.min;

					auto newx = cos_theta * x + sin_theta * z;
					auto newz = -sin_theta * x + cos_theta * z;

					glm::vec3 tester(newx, y, newz);

					for (int c = 0; c < 3; c++) {
						min[c] = std::fmin(min[c], tester[c]);
						max[c] = std::fmax(max[c], tester[c]);
					}
				}
			}
		}

		bbox = aabb(min, max);
	}

	bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override {

		// Transform the ray from world space to object space.

		auto origin = glm::vec3(
			(cos_theta * r.origin.x) - (sin_theta * r.origin.z),
			r.origin.y,
			(sin_theta * r.origin.x) + (cos_theta * r.origin.z)
		);

		auto direction = glm::vec3(
			(cos_theta * r.direction.x) - (sin_theta * r.direction.z),
			r.direction.y,
			(sin_theta * r.direction.x) + (cos_theta * r.direction.z)
		);

		Ray rotated_r(origin, direction);

		// Determine whether an intersection exists in object space (and if so, where).

		if (!object->hit(rotated_r, ray_t, rec))
			return false;

		// Transform the intersection from object space back to world space.

		rec.position = glm::vec3(
			(cos_theta * rec.position.x) + (sin_theta * rec.position.z),
			rec.position.y,
			(-sin_theta * rec.position.x) + (cos_theta * rec.position.z)
		);

		rec.normal = glm::vec3(
			(cos_theta * rec.normal.x) + (sin_theta * rec.normal.z),
			rec.normal.y,
			(-sin_theta * rec.normal.x) + (cos_theta * rec.normal.z)
		);

		return true;
	}
	aabb bounding_box() const override { return bbox; }

private:
	shared_ptr<Hittable> object;
	double sin_theta;
	double cos_theta;
	aabb bbox;
};
#endif
