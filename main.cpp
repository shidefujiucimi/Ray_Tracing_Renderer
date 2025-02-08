#include <iostream>
#include <fstream>

#include <ray.h>
#include <camera.h>

using namespace std;
//the amount of rays per pixel
#define amount_of_rays_per_pixel 1
//从每个pixel打出的rays
static Ray rays[amount_of_rays_per_pixel];

void RenderToimage(Camera camera, Scene scene, const char* _Filename);
void Raygenerator(glm::vec3 camerapos, glm::vec3 pixelpos);

void main() {
    Camera maincamera(glm::vec3(0.0,0.0,0.0));
    Scene mainscene(
        {
            Sphere(glm::vec3(0.0, 0.0, -10.0), 3.0) 
        } 
    );
    RenderToimage(maincamera, mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.ppm");
    RenderToimage(maincamera, mainscene, "D:/VS project/Ray_Tracing_Renderer/out image/outimage.txt");
    
}
//逐像素调用ray的shade函数
void RenderToimage(Camera camera, Scene scene,const char*_Filename) {
    ofstream outimage;
    outimage.open(_Filename);
    glm::vec3 color;//color的范围是（0,1）
    glm::vec3 pixelposition = camera.pixel00_loc;

    outimage << "P3\n" << camera.resolutionx << ' ' << camera.resolutiony << "\n255\n";
    for (int j = 0; j < camera.resolutiony; j++) {
        for (int i = 0; i < camera.resolutionx; i++) {
            color = glm::vec3(0.0, 0.0, 0.0);
            Raygenerator(camera.Position, pixelposition);
            for (int i = 0; i < amount_of_rays_per_pixel; i++) {
                color += rays[i].Shade(scene);
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