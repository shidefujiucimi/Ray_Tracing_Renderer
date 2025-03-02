#include <quad.h>
#include <sphere.h>
quad::quad(const glm::vec3& Q, const glm::vec3& u, const glm::vec3& v, shared_ptr<material> mat)
    : Q(Q), u(u), v(v), mat(mat)
{
    glm::vec3 n = cross(u, v);
    normal = normalize(n);
    D = dot(normal, Q);
    w = n / dot(n, n);
    area = length(n);
    set_bounding_box();
}
void quad::set_bounding_box() {
    // Compute the bounding box of all four vertices.
    auto bbox_diagonal1 = aabb(Q, Q + u + v);
    auto bbox_diagonal2 = aabb(Q + u, Q + v);
    bbox = aabb(bbox_diagonal1, bbox_diagonal2);
}
aabb quad::bounding_box() const{ return bbox; }
bool quad::hit(const Ray& r, interval ray_t, Hit_record& rec) const{
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
bool quad::is_interior(double a, double b, Hit_record& rec) const {
    interval unit_interval = interval(0, 1);
    // Given the hit point in plane coordinates, return false if it is outside the
    // primitive, otherwise set the hit record UV coordinates and return true.

    if (!unit_interval.contains(a) || !unit_interval.contains(b))
        return false;

    //rec.u = a;
    //rec.v = b;
    return true;
}
double quad::pdf_value(const glm::vec3& origin, const glm::vec3& direction) const{
    Hit_record rec;
    if (!this->hit(Ray(origin, direction), interval(0.001, infinity), rec))
        return 0;
    
    auto distance = rec.t * length(direction);
    auto distance_squared = distance* distance;
    auto cosine = std::fabs(dot(direction, rec.normal) / length(direction));

    return distance_squared / (cosine * area);
}
glm::vec3 quad::random(const glm::vec3& origin) const{
    auto p = Q + (float(random_double()) * u) + (float(random_double()) * v);
    return p - origin;
}
shared_ptr<hittable_list> box(const glm::vec3& a, const glm::vec3& b, shared_ptr<material> mat)
{
    // Returns the 3D box (six sides) that contains the two opposite vertices a & b.

    std::shared_ptr< hittable_list> sides = make_shared<hittable_list>();

    // Construct the two opposite vertices with the minimum and maximum coordinates.
    glm::vec3 min = glm::vec3(std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z));
    glm::vec3 max = glm::vec3(std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z));

    glm::vec3 dx = glm::vec3(max.x - min.x, 0, 0);
    glm::vec3 dy = glm::vec3(0, max.y - min.y, 0);
    glm::vec3 dz = glm::vec3(0, 0, max.z - min.z);

    sides->add(make_shared<quad>(glm::vec3(min.x, min.y, max.z), dx, dy, mat)); // front
    sides->add(make_shared<quad>(glm::vec3(max.x, min.y, max.z), -dz, dy, mat)); // right
    sides->add(make_shared<quad>(glm::vec3(max.x, min.y, min.z), -dx, dy, mat)); // back
    sides->add(make_shared<quad>(glm::vec3(min.x, min.y, min.z), dz, dy, mat)); // left
    sides->add(make_shared<quad>(glm::vec3(min.x, max.y, max.z), dx, -dz, mat)); // top
    sides->add(make_shared<quad>(glm::vec3(min.x, min.y, min.z), dx, dz, mat)); // bottom

    return sides;
}

Sphere::Sphere(const glm::vec3& static_center, double radius, shared_ptr<material> mat)
    : center(glm::vec3(0, 0, 0), static_center), radius(std::fmax(0, radius)), mat(mat)
{
    glm::vec3 rvec = glm::vec3(radius, radius, radius);
    bbox = aabb(static_center - rvec, static_center + rvec);
}
bool Sphere::hit(const Ray& r, interval ray_t, Hit_record& rec)const{
    glm::vec3 oc = center.direction - r.origin;
    double a = dot(r.direction, r.direction);
    double b = -2.0 * dot(r.direction, oc);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    double root = 0.0;
    if (discriminant < 0) {
        return false;
    }
    else {
        root = (-b - std::sqrt(discriminant)) / (2.0 * a);
        if (root <= ray_t.min || ray_t.max <= root)
            return false;
    }

    rec.t = root;
    rec.position = r.at(rec.t);
    rec.normal = (rec.position - center.direction) / radius;
    glm::vec3 outward_normal = (rec.position - center.direction) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;

}
aabb Sphere::bounding_box() const{ return bbox; }