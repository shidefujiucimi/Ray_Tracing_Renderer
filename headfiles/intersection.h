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

