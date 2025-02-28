#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <limits>
#include <memory>
#include <algorithm>

// Common Headers
#include <ray.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min,double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}
inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return int(random_double(min, max + 1));
}
static glm::vec3 random_vec3() {
    return glm::vec3(random_double(), random_double(), random_double());
}
//Return a random vector that falls within the unit cube
static glm::vec3 random_vec3(double min, double max) {
    return glm::vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}
//Return a random vector that falls within the standard sphere
inline glm::vec3 random_unit_vec3() {
    while (true) {
        glm::vec3 p = random_vec3(-1, 1);
        float lensq =glm::length(p);
        //std::cout << lensq << std::endl;
        if (1e-160 < lensq && lensq <= 1)
            return p / lensq;
    }
}
//Return a random vector that falls within the unit hemisphere
inline glm::vec3 random_unit_vec3_on_hemisphere(glm::vec3 normal) {
    glm::vec3 on_unit_sphere = random_unit_vec3();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}
inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}
inline bool near_zero(glm::vec3 e){
    // Return true if the vector is close to zero in all dimensions.
    auto s = 1e-8;
    return (std::fabs(e.x) < s) && (std::fabs(e.y) < s) && (std::fabs(e.z) < s);
}

#endif
