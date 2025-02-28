#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include <hittable.h>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public Hittable {
public:
    std::vector<shared_ptr<Hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    aabb bounding_box() const override { return bbox; }
    void add(shared_ptr<Hittable> object) {
        objects.push_back(object);
        bbox = aabb(bbox, object->bounding_box());
    }
    bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override {
        Hit_record temp_rec;
        bool hit_anything = false;
        float closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
    

private:
    aabb bbox;
};

#endif
