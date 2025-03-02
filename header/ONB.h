#ifndef ONB_H
#define ONB_H
#include <common_header.h>
class onb {
public:
    onb(const glm::vec3& n);
    const glm::vec3& u() const;
    const glm::vec3& v() const;
    const glm::vec3& w() const;
    glm::vec3 transform(const glm::vec3& v) const;
private:
    glm::vec3 axis[3];
};


#endif
