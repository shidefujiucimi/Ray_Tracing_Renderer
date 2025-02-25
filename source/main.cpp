#include <common_header.h>
#include <camera.h>
#include <hittable_list.h>
#include <sphere.h>
using namespace std;

void main() {
    hittable_list mainscene;
    //material
    shared_ptr<lambertian> material_ground = make_shared<lambertian>(glm::vec3(0.8, 0.8, 0.0));
    shared_ptr<lambertian> material_center = make_shared<lambertian>(glm::vec3(0.1, 0.2, 0.5));
    shared_ptr<dielectric> material_left = make_shared<dielectric>(1.50);
    shared_ptr<dielectric> material_bubble = make_shared<dielectric>(1.00 / 1.50);
    shared_ptr<metal> material_right = make_shared<metal>(glm::vec3(0.8, 0.6, 0.2),0.7);
    //geometry
    mainscene.add(make_shared<Sphere>(glm::vec3(0, 0, -5), 2, material_center));
    mainscene.add(make_shared<Sphere>(glm::vec3(0, -102, -5), 100, material_ground));
    mainscene.add(make_shared<Sphere>(glm::vec3(-5, 0, -5), 2, material_left));
    mainscene.add(make_shared<Sphere>(glm::vec3(-5, 0, -5), 1.5, material_bubble));
    mainscene.add(make_shared<Sphere>(glm::vec3(5, 0, -5), 2, material_right));

    Camera maincamera(glm::vec3(0.0, 0.0, 0.0));

    maincamera.AA = true;
    maincamera.samples_per_pixel = 50;
    maincamera.max_depth = 100;
    maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    //maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");
    
}


