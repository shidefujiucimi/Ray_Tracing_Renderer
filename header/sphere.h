#ifndef SPHERE_H
#define SPHERE_H
#include <hittable.h>
class Sphere :public Hittable {
public:
	//Sphere(glm::vec3 static_center, float radiusinput, shared_ptr<material> matinput)
	//	: center(glm::vec3(0, 0, 0),static_center), radius(std::fmax(0, radiusinput)) ,mat(matinput){}
	Sphere(const glm::vec3& static_center, double radius, shared_ptr<material> mat)
		: center(glm::vec3(0, 0, 0),static_center), radius(std::fmax(0, radius)), mat(mat)
	{
		glm::vec3 rvec = glm::vec3(radius, radius, radius);
		bbox = aabb(static_center - rvec, static_center + rvec);
	}
	bool hit(const Ray& r, interval ray_t, Hit_record& rec)const override {
		glm::vec3 oc = center.direction - r.origin;
		double a = dot(r.direction, r.direction);
		double b = -2.0 * dot(r.direction, oc);
		double c = dot(oc, oc) - radius * radius;
		double discriminant = b * b - 4 * a * c;
		double root = 0.0;
		if (discriminant < 0) {
			return false;
		}
		else {
			root = (-b - std::sqrt(discriminant)) / (2.0 * a);
			if (root <= ray_t.min || ray_t.max <= root)
				return false;	
		}
	
		rec.t = root;
		rec.position = r.at(rec.t);
		rec.normal = (rec.position - center.direction) / radius;
		glm::vec3 outward_normal = (rec.position - center.direction) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.mat = mat;

		return true;

	}
	aabb bounding_box() const override { return bbox; }
private:
	float radius;
	Ray center;
	shared_ptr<material> mat;
	aabb bbox;
};


#endif // !1

