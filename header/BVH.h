#ifndef BVH_H
#define BVH_H

#include <aabb.h>
#include <hittable.h>

class bvh_node : public Hittable {
public:
    bvh_node(hittable_list list) : bvh_node(list.objects, 0, list.objects.size()) {
        
    };
    bvh_node(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end);
    bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override;
    aabb bounding_box() const override { return bbox; }

private:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    aabb bbox;

    static bool box_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis_index);
    static bool box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
    static bool box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
    static bool box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
};

#endif
