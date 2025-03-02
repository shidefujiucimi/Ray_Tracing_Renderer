#ifndef QUAD_H
#define QUAD_H

#include <hittable.h>

class quad : public Hittable {
public:
    //Q is the starting corner,while u and v are two sides which orign is Q
    quad(const glm::vec3& Q, const glm::vec3& u, const glm::vec3& v, shared_ptr<material> mat);
       
    virtual void set_bounding_box();
    aabb bounding_box() const override;

    //Ray - quad intersection will be determined in three steps :
    //1.finding the plane that contains that quad,
    //2.solving for the intersection of a ray and the quad - containing plane,
    //3.determining if the hit point lies inside the quad.
    bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override;
    virtual bool is_interior(double a, double b, Hit_record& rec) const;
    double pdf_value(const glm::vec3& origin, const glm::vec3& direction) const override;
    glm::vec3 random(const glm::vec3& origin) const override;

private:
    glm::vec3 Q;
    glm::vec3 u, v;
    glm::vec3 w;
    shared_ptr<material> mat;
    aabb bbox;
    glm::vec3 normal;
    double D;
    double area;
};
shared_ptr<hittable_list> box(const glm::vec3& a, const glm::vec3& b, shared_ptr<material> mat);
#endif