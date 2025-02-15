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
	


	float hittable(glm::vec3 orign,glm::vec3 direction) const {//�ҵ����������ཻ��t
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

	PointOfIntersection intersection(glm::vec3 orign, glm::vec3 direction, float t) const {//���ݸ�����t������������ཻ�ĵ����Ϣ
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

		for (int i=0; i < objects.size(); i++) {//Ѱ������Ľ����t
			float t = objects[i].hittable(orign,direction);
			if (t != -1.0 && t < T) {
				T = t;
				ID = i;
			}
		}
		if (ID == -1) {//���û���ҵ�����
			PointOfIntersection pointofintersection;
			pointofintersection.existance = false;
			return pointofintersection;
		}
		else {//����ҵ��˽���
			return objects[ID].intersection(orign, direction, T);
		}
	}
private:

};






#endif // !SCENE_H

