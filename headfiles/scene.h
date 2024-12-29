#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

//这个头文件用于处理intersection问题
class PointOfIntersection {
public:
	bool existance;
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 albedo;
	PointOfIntersection(glm::vec3 positioninput, glm::vec3 normalinput, glm::vec3 albedoinput)
		: position(positioninput), normal(normalinput), albedo(albedoinput){
		
	}
	PointOfIntersection() {

	}
private:


};
class Sphere {
public:
	float radius;
	glm::vec3 center;
	glm::vec3 albedo;
	Sphere(glm::vec3 centerinput, float radiusinput) : center(centerinput), radius(radiusinput) {

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

//BVH 加速结构(Bounding volume hierarchy
class BVH {
public:

private:

};




#endif // !SCENE_H

