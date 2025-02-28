#ifndef QUAD_H
#define QUAD_H

#include <hittable.h>

class quad : public Hittable {
public:
    //Q is the starting corner,while u and v are two sides which orign is Q
    quad(const glm::vec3& Q, const glm::vec3& u, const glm::vec3& v, shared_ptr<material> mat)
        : Q(Q), u(u), v(v), mat(mat)
    {
        glm::vec3 n = cross(u, v);
        normal = normalize(n);
        D = dot(normal, Q);
        w = n / dot(n, n);
        set_bounding_box();
    }

    virtual void set_bounding_box() {
        // Compute the bounding box of all four vertices.
        auto bbox_diagonal1 = aabb(Q, Q + u + v);
        auto bbox_diagonal2 = aabb(Q + u, Q + v);
        bbox = aabb(bbox_diagonal1, bbox_diagonal2);
    }

    aabb bounding_box() const override { return bbox; }

    //Ray - quad intersection will be determined in three steps :
    //1.finding the plane that contains that quad,
    //2.solving for the intersection of a ray and the quad - containing plane,
    //3.determining if the hit point lies inside the quad.
    bool hit(const Ray& r, interval ray_t, Hit_record& rec) const override {
        float denom = dot(normal, r.direction);

        // No hit if the ray is parallel to the plane.
        if (std::fabs(denom) < 1e-8)
            return false;

        // Return false if the hit point parameter t is outside the ray interval.
        double t = (D - dot(normal, r.origin)) / denom;
        if (!ray_t.contains(t))
            return false;

        // Determine if the hit point lies within the planar shape using its plane coordinates.
        glm::vec3 intersection = r.at(t);
        glm::vec3 planar_hitpt_vector = intersection - Q;
        float alpha = dot(w, cross(planar_hitpt_vector, v));
        float beta = dot(w, cross(u, planar_hitpt_vector));

        if (!is_interior(alpha, beta, rec))
            return false;

        rec.t = t;
        rec.position = intersection;
        rec.mat = mat;
        rec.set_face_normal(r, normal);

        return true;
    }

    virtual bool is_interior(double a, double b, Hit_record& rec) const {
        interval unit_interval = interval(0, 1);
        // Given the hit point in plane coordinates, return false if it is outside the
        // primitive, otherwise set the hit record UV coordinates and return true.

        if (!unit_interval.contains(a) || !unit_interval.contains(b))
            return false;

        //rec.u = a;
        //rec.v = b;
        return true;
    }
private:
    glm::vec3 Q;
    glm::vec3 u, v;
    glm::vec3 w;
    shared_ptr<material> mat;
    aabb bbox;
    glm::vec3 normal;
    double D;
};

#endif