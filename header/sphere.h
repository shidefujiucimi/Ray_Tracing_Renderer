#ifndef SPHERE_H
#define SPHERE_H
#include <hittable.h>
#include <ONB.h>
class Sphere :public Hittable {
public:
	//Sphere(glm::vec3 static_center, float radiusinput, shared_ptr<material> matinput)
	//	: center(glm::vec3(0, 0, 0),static_center), radius(std::fmax(0, radiusinput)) ,mat(matinput){}
	Sphere(const glm::vec3& static_center, double radius, shared_ptr<material> mat);

	bool hit(const Ray& r, interval ray_t, Hit_record& rec)const override;
	aabb bounding_box() const override;
    double pdf_value(const glm::vec3& origin, const glm::vec3& direction) const override;
    glm::vec3 random(const glm::vec3& origin) const override;
private:
	float radius;
	Ray center;
	shared_ptr<material> mat;
	aabb bbox;
	static glm::vec3 random_to_sphere(double radius, double distance_squared);
};

#endif 

