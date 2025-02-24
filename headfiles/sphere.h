#ifndef SPHERE_H
#define SPHERE_H
#include <hittable.h>
class Sphere :public Hittable {
public:
	Sphere(glm::vec3 centerinput, float radiusinput) : center(centerinput), radius(radiusinput) {

	}
	bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec)const override {
		glm::vec3 oc = center - r.origin;
		auto a = dot(r.direction, r.direction);
		auto b = -2.0 * dot(r.direction, oc);
		auto c = dot(oc, oc) - radius * radius;
		auto discriminant = b * b - 4 * a * c;
		double root = 0.0;
		if (discriminant < 0) {
			return false;
		}
		else {
			root=(-b - std::sqrt(discriminant)) / (2.0 * a);
		}
	
		rec.t = root;
		rec.position = r.at(rec.t);
		rec.normal = (rec.position - center) / radius;
		glm::vec3 outward_normal = (rec.position - center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}

private:
	float radius;
	glm::vec3 center;
	glm::vec3 albedo;
};


#endif // !1

