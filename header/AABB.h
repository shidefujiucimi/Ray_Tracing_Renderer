#ifndef AABB_H
#define AABB_H
#include <common_header.h>
#include <interval.h>
class aabb {
public:
    interval x, y, z;

    aabb(){} 
    aabb(const interval& x, const interval& y, const interval& z);
    aabb(const glm::vec3& a, const glm::vec3& b);
    aabb(const aabb& box0, const aabb& box1);

    const interval& axis_interval(int n) const;
    bool hit(const Ray& r, interval ray_t) const;

private:
    void pad_to_minimums();
};
aabb operator+(const aabb& bbox, const glm::vec3& offset);
aabb operator+(const glm::vec3& offset, const aabb& bbox);

#endif
