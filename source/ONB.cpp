#include <ONB.h>
onb::onb(const glm::vec3& n) {
    axis[2] = normalize(n);
    glm::vec3 a = (std::fabs(axis[2].x) > 0.9) ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0);
    axis[1] = normalize(cross(axis[2], a));
    axis[0] = cross(axis[2], axis[1]);
}
const glm::vec3& onb::u() const { return axis[0]; }
const glm::vec3& onb::v() const { return axis[1]; }
const glm::vec3& onb::w() const { return axis[2]; }
glm::vec3 onb::transform(const glm::vec3& v) const {
    // Transform from basis coordinates to local space.
    return (v[0] * axis[0]) + (v[1] * axis[1]) + (v[2] * axis[2]);
}