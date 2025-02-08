#ifndef RAY_H
#define RAY_H


#include <intersection.h>
#include <light.h>
class Ray {
public:
	glm::vec3 orign;
	glm::vec3 direction;
	
	Ray(glm::vec3 origninput,glm::vec3 directioninput):orign(origninput),direction(directioninput) {

	}
	Ray(){
		orign = glm::vec3(0.0);
		direction = glm::vec3(0.0);
	}
	glm::vec3 at(float t) const{
		return orign + t * direction;
	}

	//shade
	glm::vec3 Shade(Scene& scene) const {
		glm::vec3 color;
		PointOfIntersection pointofintersection = scene.searchintersection(orign,direction);
		if (pointofintersection.existance == false) 
			color = glm::vec3(0.0, 0.0, 0.0);	
		else {
			color = glm::vec3(
				(pointofintersection.normal.r + 1.0) * 0.5,
				(pointofintersection.normal.g + 1.0) * 0.5,
				(pointofintersection.normal.b + 1.0) * 0.5
			);
		
		}
			
		return color;
	}
	
private:
	
};

#endif

