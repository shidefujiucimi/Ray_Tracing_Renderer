#include<AABB.h>
aabb::aabb(const interval& x, const interval& y, const interval& z) : x(x), y(y), z(z) {
    pad_to_minimums();
}
aabb::aabb(const glm::vec3& a, const glm::vec3& b) {
    // Treat the two points a and b as extrema for the bounding box, so we don't require a
    // particular minimum/maximum coordinate order.

    x = (a.x <= b.x) ? interval(a.x, b.x) : interval(b.x, a.x);
    y = (a.y <= b.y) ? interval(a.y, b.y) : interval(b.y, a.y);
    z = (a.z <= b.z) ? interval(a.z, b.z) : interval(b.z, a.z);

    pad_to_minimums();
}
aabb::aabb(const aabb& box0, const aabb& box1) {
    x = interval(box0.x, box1.x);
    y = interval(box0.y, box1.y);
    z = interval(box0.z, box1.z);
    pad_to_minimums();
}

const interval& aabb::axis_interval(int n) const {
    if (n == 1) return y;
    if (n == 2) return z;
    return x;
}
bool aabb::hit(const Ray& r, interval ray_t) const {
    const glm::vec3& ray_orig = r.origin;
    const glm::vec3& ray_dir = r.direction;

    for (int axis = 0; axis < 3; axis++) {
        const interval& ax = axis_interval(axis);
        const double adinv = 1.0 / ray_dir[axis];

        double t0 = (ax.min - ray_orig[axis]) * adinv;
        double t1 = (ax.max - ray_orig[axis]) * adinv;

        if (t0 < t1) {
            if (t0 > ray_t.min) ray_t.min = t0;
            if (t1 < ray_t.max) ray_t.max = t1;
        }
        else {
            if (t1 > ray_t.min) ray_t.min = t1;
            if (t0 < ray_t.max) ray_t.max = t0;
        }

        if (ray_t.max <= ray_t.min)
            return false;
    }
    return true;
}
void aabb::pad_to_minimums() {
    // Adjust the AABB so that no side is narrower than some delta, padding if necessary.

    double delta = 0.0001;
    if (x.size() < delta)
        x.expand(delta);
    if (y.size() < delta)
        y.expand(delta);
    if (z.size() < delta)
        z.expand(delta);
}

aabb operator+(const aabb& bbox, const glm::vec3& offset) {
    return aabb(bbox.x + offset.x, bbox.y + offset.y, bbox.z + offset.z);
}
aabb operator+(const glm::vec3& offset, const aabb& bbox) {
    return bbox + offset;
}