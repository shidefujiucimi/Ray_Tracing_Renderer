#include <common_header.h>
#include <camera.h>
#include <hittable_list.h>
#include <sphere.h>

using namespace std;

#define amount_of_rays_per_pixel 1
static Ray rays[amount_of_rays_per_pixel];

void RenderToimage(Camera camera, hittable_list scene, const char* _Filename);
void Raygenerator(glm::vec3 camerapos, glm::vec3 pixelpos);
glm::vec3 Shade(Ray& ray, double ray_tmin, double ray_tmax, hittable_list& scene);

void main() {
    Camera maincamera(glm::vec3(0.0,0.0,0.0));

    hittable_list mainscene;
    mainscene.add(make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5));
    mainscene.add(make_shared<Sphere>(glm::vec3(0, -100.5, -1), 100));

    RenderToimage(maincamera, mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    RenderToimage(maincamera, mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");
    
}
//逐像素调用shade函数
void RenderToimage(Camera camera, hittable_list scene,const char*_Filename) {
    ofstream outimage;
    outimage.open(_Filename);
    glm::vec3 color;//color的范围是（0,1）
    glm::vec3 pixelposition = camera.pixel00_loc;

    outimage << "P3\n" << camera.resolutionx << ' ' << camera.resolutiony << "\n255\n";
    for (int j = 0; j < camera.resolutiony; j++) {
        for (int i = 0; i < camera.resolutionx; i++) {
            color = glm::vec3(0.0, 0.0, 0.0);
            Raygenerator(camera.Position, pixelposition);
            for (int k = 0; k < amount_of_rays_per_pixel; k++) {
                color += Shade(rays[k],0.0,infinity, scene);
            }
            color /= amount_of_rays_per_pixel;
            
            int ir = int(255.999 * color.r);
            int ig = int(255.999 * color.g);
            int ib = int(255.999 * color.b);

            outimage << ir << ' ' << ig << ' ' << ib << '\n';
            //outimage << direction.r << ' ' << direction.g << ' ' << direction.b << '\n';

            pixelposition += (camera.canvas_width / camera.resolutionx) * camera.Right;
        }
        pixelposition -= camera.canvas_width * camera.Right;
        pixelposition -= (camera.canvas_height / camera.resolutiony) * camera.Up;

    }
    outimage.close();
    cout << "finish" << endl;
}
//ray generator
static void Raygenerator(glm::vec3 camerapos,glm::vec3 pixelpos) {
    glm::vec3 direction = pixelpos - camerapos;
    rays[0] = Ray(camerapos, direction);
}

//shade
glm::vec3 Shade(Ray& ray,double ray_tmin,double ray_tmax, hittable_list& scene) {
    glm::vec3 color;
    Hit_record hit_record;
    if (scene.hit(ray, ray_tmin, ray_tmax, hit_record) == false)
        color = glm::vec3(0.0, 0.0, 0.0);
    else {
        color = glm::vec3(
            (hit_record.normal.r + 1.0) * 0.5,
            (hit_record.normal.g + 1.0) * 0.5,
            (hit_record.normal.b + 1.0) * 0.5
        );

    }

    return color;
}