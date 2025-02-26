#include <common_header.h>
#include <camera.h>
#include <hittable_list.h>
#include <sphere.h>
using namespace std;

void main() {
    hittable_list mainscene;
    //material
    //shared_ptr<lambertian> material_ground = make_shared<lambertian>(glm::vec3(0.8, 0.8, 0.0));
    //shared_ptr<lambertian> material_center = make_shared<lambertian>(glm::vec3(0.1, 0.2, 0.5));
    //shared_ptr<dielectric> material_left = make_shared<dielectric>(1.50);
    //shared_ptr<dielectric> material_bubble = make_shared<dielectric>(1.00 / 1.50);
    //shared_ptr<metal> material_right = make_shared<metal>(glm::vec3(0.8, 0.6, 0.2),0.7);
    //geometry
    //mainscene.add(make_shared<Sphere>(glm::vec3(0, 0, -5), 2, material_center));
    //mainscene.add(make_shared<Sphere>(glm::vec3(0, -102, -5), 100, material_ground));
    //mainscene.add(make_shared<Sphere>(glm::vec3(-5, 0, -5), 2, material_left));
    //mainscene.add(make_shared<Sphere>(glm::vec3(-5, 0, -5), 1.5, material_bubble));
    //mainscene.add(make_shared<Sphere>(glm::vec3(5, 0, -5), 2, material_right));


    shared_ptr<lambertian> ground_material = make_shared<lambertian>(glm::vec3(0.5, 0.5, 0.5));
    mainscene.add(make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {
            double choose_mat = random_double();
            glm::vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    glm::vec3 albedo = random_unit_vec3() * random_unit_vec3();
                    sphere_material = make_shared<lambertian>(albedo);
                    mainscene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    glm::vec3 albedo = random_vec3(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    mainscene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    mainscene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    shared_ptr<dielectric> material1 = make_shared<dielectric>(1.5);
    mainscene.add(make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, material1));

    shared_ptr<lambertian> material2 = make_shared<lambertian>(glm::vec3(0.4, 0.2, 0.1));
    mainscene.add(make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, material2));

    shared_ptr<metal> material3 = make_shared<metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
    mainscene.add(make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, material3));

    Camera maincamera(glm::vec3(7.0, 2.0, 3.0), glm::vec3(0.0, 45.0, 0.0));

    maincamera.AA = true;
    maincamera.samples_per_pixel = 100;
    maincamera.max_depth = 100;
    maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    //maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");
    
}


