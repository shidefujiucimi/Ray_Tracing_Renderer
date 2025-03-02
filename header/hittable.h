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
	Hit_record();
	void set_face_normal(const Ray& r, const glm::vec3& outward_normal);
};
class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& r,interval ray_t, Hit_record& rec)const = 0;
	virtual aabb bounding_box() const = 0;
	virtual double pdf_value(const glm::vec3& origin, const glm::vec3& direction) const {
		return 0.0;
	}
	virtual glm::vec3 random(const glm::vec3& origin) const {
		return glm::vec3(1, 0, 0);
	}

}; 
class translate : public Hittable {
public:
	translate(shared_ptr<Hittable> object, const glm::vec3& offset);
	bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override;
	aabb bounding_box() const override;
private:
	shared_ptr<Hittable> object;
	glm::vec3 offset;
	aabb bbox;
};
class rotate_y : public Hittable {
public:
	rotate_y(shared_ptr<Hittable> object, double angle);
	bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override;
	aabb bounding_box() const override;

private:
	shared_ptr<Hittable> object;
	double sin_theta;
	double cos_theta;
	aabb bbox;
};
class hittable_list : public Hittable {
public:
	std::vector<shared_ptr<Hittable>> objects;

	hittable_list();
	hittable_list(shared_ptr<Hittable> object);

	void clear();
	aabb bounding_box() const override;
	void add(shared_ptr<Hittable> object);
	bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override;
private:
	aabb bbox;
};
#endif
