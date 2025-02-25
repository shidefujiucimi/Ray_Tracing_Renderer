#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

#include <hittable_list.h>
#include <common_header.h>
using namespace std;
class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::mat4 view;

    glm::vec3 Front = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 Right = glm::vec3(1.0, 0.0, 0.0);
    glm::vec3 Up = glm::vec3(0.0, 1.0, 0.0);

    int resolutionx = 1080;
    int resolutiony = 720;

    float focal_length = 1.0f;//½¹¾à
    float fovy=45.0f;//fovy Specifies the field of view angle in the y direction
    glm::vec3 optical_center;
    glm::vec3 pixel00_loc;
    float canvas_width;
    float canvas_height;
    
    float pixel_width;
    float pixel_height;
    
    int samples_per_pixel=1;
    int max_depth = 10;//Maxinum number of child rays

    bool AA = false;

    Camera(glm::vec3 Positioninput);
    Camera(glm::vec3 Positioninput, glm::vec3 Rotationinput);

    void SetPosition(glm::vec3 Positioninput);
    void SetRotation(glm::vec3 Rotationinput);
    void SetFocal(float focal);
    void SetZoom(float fovyinput);
    void SetResolution(float x, float y);
    void RenderToimage(hittable_list& scene, const char* _Filename);

private:
    glm::vec3 calRight(glm::vec3 Front);
    void write_color(const glm::vec3& color, ofstream& outimage);
    glm::vec3 Shade(const Ray& ray, double ray_tmin, double ray_tmax, const hittable_list& scene,int depth);
    void multisample(int i,int j, ofstream& outimage, hittable_list scene);
    Ray get_ray(int i, int j) const;
    glm::vec3 sample_square() const;
};

#endif

