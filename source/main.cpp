#include <common_header.h>
#include <camera.h>
#include <hittable_list.h>
#include <sphere.h>

using namespace std;

//#define amount_of_rays_per_pixel 1
//static Ray rays[amount_of_rays_per_pixel];


void main() {
    

    hittable_list mainscene;
    //material
    auto material_ground = make_shared<lambertian>(glm::vec3(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(glm::vec3(0.1, 0.2, 0.5));
    //auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8));
    //auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));
    //geometry
    mainscene.add(make_shared<Sphere>(glm::vec3(0, 0, -5), 2, material_center));
    mainscene.add(make_shared<Sphere>(glm::vec3(0, -102, -5), 100, material_ground));

    Camera maincamera(glm::vec3(0.0, 0.0, 0.0));

    maincamera.AA = true;
    maincamera.samples_per_pixel = 4;
    maincamera.max_depth = 100;
    maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    //maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");

}


