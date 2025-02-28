#include <BVH.h>
bvh_node::bvh_node(std::vector<shared_ptr<Hittable>>& objects, size_t start, size_t end) {
    int axis = random_int(0, 2);

    auto comparator = (axis == 0) ? box_x_compare
        : (axis == 1) ? box_y_compare
        : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
        
    }
    else if (object_span == 2) {
        left = objects[start];
        right = objects[start + 1];
        
    }
    else {
        std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

        auto mid = start + object_span / 2;
        left = make_shared<bvh_node>(objects, start, mid);
        right = make_shared<bvh_node>(objects, mid, end);
    }

    bbox = aabb(left->bounding_box(), right->bounding_box());
    
}
bool bvh_node::hit(const Ray& r, interval ray_t, Hit_record& rec) const{
    if (!bbox.hit(r, ray_t))
        return false;

    bool hit_left = left->hit(r, ray_t, rec);
    bool hit_right = right->hit(r, interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

    return hit_left || hit_right;
}
bool bvh_node::box_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis_index) {
    auto a_axis_interval = a->bounding_box().axis_interval(axis_index);
    auto b_axis_interval = b->bounding_box().axis_interval(axis_index);
    return a_axis_interval.min < b_axis_interval.min;
}
bool bvh_node::box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return box_compare(a, b, 0);
}
bool bvh_node::box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return box_compare(a, b, 1);
}
bool bvh_node::box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return box_compare(a, b, 2);
}