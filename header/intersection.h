#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <ray.h>

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

