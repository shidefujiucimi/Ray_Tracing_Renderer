#ifndef SPHERE_H
#define SPHERE_H
#include <hittable.h>
class Sphere :public Hittable {
public:
	Sphere(glm::vec3 centerinput, float radiusinput) : center(centerinput), radius(radiusinput) {

	}
	bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec)const override {
		glm::vec3 oc = center - r.Origin();
		auto a = r.Direction().length();
		auto h = dot(r.Direction(), oc);
		auto c = oc.length() - radius * radius;

		auto discriminant = h * h - a * c;
		if (discriminant < 0)
			return false;

		auto sqrtd = std::sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (h - sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root) {
			root = (h + sqrtd) / a;
			if (root <= ray_tmin || ray_tmax <= root)
				return false;
		}

		rec.t = root;
		rec.position = r.at(rec.t);
		rec.normal = (rec.position - center) / radius;

		return true;
	}

private:
	float radius;
	glm::vec3 center;
	glm::vec3 albedo;
};


#endif // !1

