#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Ray {
public:
	glm::vec3 origin;
	glm::vec3 direction;
	Ray(glm::vec3 origininput,glm::vec3 directioninput):origin(origininput),direction(directioninput) {

	}
	Ray(){
		origin = glm::vec3(0.0);
		direction = glm::vec3(0.0);
	}
	glm::vec3 at(float t) const{
		return origin + t * direction;
	}
private:
	
};

#endif

