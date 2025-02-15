#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Ray {
public:
	Ray(glm::vec3 origninput,glm::vec3 directioninput):orign(origninput),direction(directioninput) {

	}
	Ray(){
		orign = glm::vec3(0.0);
		direction = glm::vec3(0.0);
	}
	glm::vec3 at(float t) const{
		return orign + t * direction;
	}
	glm::vec3 Orign() const {
		return orign;
	}
	glm::vec3 Dircection() const {
		return direction;
	}
private:
	glm::vec3 orign;
	glm::vec3 direction;
};

#endif

