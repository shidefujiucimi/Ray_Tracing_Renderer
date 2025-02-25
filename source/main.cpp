#include <common_header.h>
#include <camera.h>
#include <hittable_list.h>
#include <sphere.h>

using namespace std;

//#define amount_of_rays_per_pixel 1
//static Ray rays[amount_of_rays_per_pixel];


void main() {
    Camera maincamera(glm::vec3(0.0,0.0,0.0));

    hittable_list mainscene;
    mainscene.add(make_shared<Sphere>(glm::vec3(0, 0, -5), 2));
    mainscene.add(make_shared<Sphere>(glm::vec3(0, -102, -5), 100));

    maincamera.AA = true;
    maincamera.samples_per_pixel = 4;
    maincamera.max_depth = 100;
    maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    //maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");

    //random_unit_vec3();

}


