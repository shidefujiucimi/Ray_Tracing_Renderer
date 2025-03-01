#include <common_header.h>
#include <camera.h>
#include <hittable_list.h>
#include <sphere.h>
#include <quad.h>
#include <BVH.h>
using namespace std;
void scene_random_spheres();
void scene_three_spheres();
void scene_quads();
void cornell_box();
void main() {
    switch (4) {
    case 1:  scene_random_spheres();  break;
    case 2:  scene_three_spheres(); break;
    case 3:  scene_quads(); break;
    case 4:  cornell_box(); break;
    }
}

void scene_random_spheres() {
    hittable_list mainscene;
    
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

    mainscene = hittable_list(make_shared<bvh_node>(mainscene));
    std::cout << "BVH finish" << std::endl;
    Camera maincamera(glm::vec3(7.0, 2.0, 3.0), glm::vec3(0.0, 45.0, 0.0));

    maincamera.samples_per_pixel = 20;
    maincamera.max_depth = 100;
    maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    //maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");

}
void scene_three_spheres() {
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
}
void scene_quads() {
    hittable_list world;

    // Materials
    shared_ptr<lambertian> left_red = make_shared<lambertian>(glm::vec3(1.0, 0.2, 0.2));
    shared_ptr<lambertian> back_green = make_shared<lambertian>(glm::vec3(0.2, 1.0, 0.2));
    shared_ptr<lambertian> right_blue = make_shared<lambertian>(glm::vec3(0.2, 0.2, 1.0));
    shared_ptr<lambertian> upper_orange = make_shared<lambertian>(glm::vec3(1.0, 0.5, 0.0));
    shared_ptr<lambertian> lower_teal = make_shared<lambertian>(glm::vec3(0.2, 0.8, 0.8));

    // Quads
    world.add(make_shared<quad>(glm::vec3(-3, -2, 5), glm::vec3(0, 0, -4), glm::vec3(0, 4, 0), left_red));
    world.add(make_shared<quad>(glm::vec3(-2, -2, 0), glm::vec3(4, 0, 0), glm::vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(glm::vec3(3, -2, 1), glm::vec3(0, 0, 4), glm::vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(glm::vec3(-2, 3, 1), glm::vec3(4, 0, 0), glm::vec3(0, 0, 4), upper_orange));
    world.add(make_shared<quad>(glm::vec3(-2, -3, 5), glm::vec3(4, 0, 0), glm::vec3(0, 0, -4), lower_teal));

    Camera maincamera(glm::vec3(0.0, 0.0, 9.0), glm::vec3(0.0, 0.0, 0.0));

    
    maincamera.samples_per_pixel = 20;
    maincamera.max_depth = 100;
    maincamera.RenderToimage(world, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    //maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");
}
void cornell_box() {
    hittable_list world;

    auto red = make_shared<lambertian>(glm::vec3(.65, .05, .05));
    auto white = make_shared<lambertian>(glm::vec3(.73, .73, .73));
    auto green = make_shared<lambertian>(glm::vec3(.12, .45, .15));
    auto light = make_shared<diffuse_light>(glm::vec3(15, 15, 15));

    world.add(make_shared<quad>(glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 555), green));
    world.add(make_shared<quad>(glm::vec3(0, 0, 0), glm::vec3(0, 555, 0), glm::vec3(0, 0, 555), red));
    world.add(make_shared<quad>(glm::vec3(343, 554, 332), glm::vec3(-130, 0, 0), glm::vec3(0, 0, -105), light));
    world.add(make_shared<quad>(glm::vec3(0, 0, 0), glm::vec3(555, 0, 0), glm::vec3(0, 0, 555), white));
    world.add(make_shared<quad>(glm::vec3(555, 555, 555), glm::vec3(-555, 0, 0), glm::vec3(0, 0, -555), white));
    world.add(make_shared<quad>(glm::vec3(0, 0, 555), glm::vec3(555, 0, 0), glm::vec3(0, 555, 0), white));

    shared_ptr<Hittable> box1 = box(glm::vec3(0, 0, 0), glm::vec3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, glm::vec3(265, 0, 295));
    world.add(box1);

    shared_ptr<Hittable> box2 = box(glm::vec3(0, 0, 0), glm::vec3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, glm::vec3(130, 0, 65));
    world.add(box2);

    Camera maincamera(glm::vec3(278, 278, -300), glm::vec3(0.0, 180, 0));

    maincamera.samples_per_pixel = 20;
    maincamera.max_depth = 100;
    maincamera.RenderToimage(world, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    //maincamera.RenderToimage(mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");
}
