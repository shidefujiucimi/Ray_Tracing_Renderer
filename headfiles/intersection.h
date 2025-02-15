#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <ray.h>



class Sphere :public Hittable {
public:
	float radius;
	glm::vec3 center;
	glm::vec3 albedo;
	Sphere(glm::vec3 centerinput, float radiusinput) : center(centerinput), radius(radiusinput) {

	}
	bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_record& rec)const override {
		return true;
	}
	


	float hittable(glm::vec3 orign,glm::vec3 direction) const {//找到光线与球相交的t
		glm::vec3 oc = center - orign;
		float a = glm::dot(direction, direction);
		float b = -2.0 * glm::dot(direction, oc);
		float c = glm::dot(oc, oc) - radius * radius;
		float discriminant = b * b - 4 * a * c;

		if (discriminant < 0) {
			return -1.0;
		}
		else {
			return (-b - std::sqrt(discriminant)) / (2.0 * a);
		}
	}

	PointOfIntersection intersection(glm::vec3 orign, glm::vec3 direction, float t) const {//根据给出的t求出光线与球相交的点的信息
		PointOfIntersection pointofintersection;
		pointofintersection.existance = true;
		pointofintersection.position = orign + t * direction;
		pointofintersection.normal = glm::normalize(pointofintersection.position - center);
		pointofintersection.albedo = albedo;
		return pointofintersection;
	}
private:

};

class Scene {
public:
	std::vector<Sphere> objects;
	Scene(std::vector<Sphere> objectsinput):objects(objectsinput) {

	}
	PointOfIntersection searchintersection(glm::vec3 orign, glm::vec3 direction) {
		float T = 1000000;
		int ID = -1;

		for (int i=0; i < objects.size(); i++) {//寻找最近的交点的t
			float t = objects[i].hittable(orign,direction);
			if (t != -1.0 && t < T) {
				T = t;
				ID = i;
			}
		}
		if (ID == -1) {//如果没有找到交点
			PointOfIntersection pointofintersection;
			pointofintersection.existance = false;
			return pointofintersection;
		}
		else {//如果找到了交点
			return objects[ID].intersection(orign, direction, T);
		}
	}
private:

};






#endif // !SCENE_H

