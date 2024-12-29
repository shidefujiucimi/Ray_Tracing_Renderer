#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
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
    
    Camera(glm::vec3 Positioninput) : Position(Positioninput){
        optical_center = Position + focal_length * Front;
        view = glm::lookAt(Position, Position + Front, Up);
        float half_height_y = focal_length * tan(glm::radians(fovy));
        float half_width_x = half_height_y  / resolutiony * resolutionx;
        pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
        canvas_width = 2 * half_width_x;
        canvas_height = 2 * half_height_y;
    }
    Camera(glm::vec3 Positioninput,glm::vec3 Rotationinput): Position(Positioninput),Rotation(Rotationinput){
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(Rotation.x), glm::vec3(1.0, 0.0, 0.0));
        trans = glm::rotate(trans, glm::radians(Rotation.y), glm::vec3(0.0, 1.0, 0.0));
        trans = glm::rotate(trans, glm::radians(Rotation.z), glm::vec3(0.0, 0.0, 1.0));

        Front = trans * glm::vec4(Front,1.0f);
        Right = trans * glm::vec4(Right, 1.0f);
        Up = trans * glm::vec4(Up, 1.0f);

        optical_center = Position + focal_length * Front;
        view = glm::lookAt(Position, Position + Front, Up);
        float half_height_y = focal_length * tan(glm::radians(fovy));
        float half_width_x = half_height_y / resolutiony * resolutionx;
        pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
        canvas_width = 2 * half_width_x;
        canvas_height = 2 * half_height_y;
    }
    void SetPosition(glm::vec3 Positioninput) {
        Position = Positioninput;
        optical_center = Position + focal_length * Front;
        pixel00_loc = optical_center + (canvas_height / 2) * Up - (canvas_width / 2) * Right;
        view = glm::lookAt(Position, Position + Front, Up);
        
    }
    void SetRotation(glm::vec3 Rotationinput) {
        Rotation = Rotationinput;
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(Rotation.x), glm::vec3(1.0, 0.0, 0.0));
        trans = glm::rotate(trans, glm::radians(Rotation.y), glm::vec3(0.0, 1.0, 0.0));
        trans = glm::rotate(trans, glm::radians(Rotation.z), glm::vec3(0.0, 0.0, 1.0));

        Front = trans * glm::vec4(Front, 1.0f);
        Right = trans * glm::vec4(Right, 1.0f);
        Up = trans * glm::vec4(Up, 1.0f);

        optical_center = Position + focal_length * Front;
        pixel00_loc = optical_center + (canvas_height / 2) * Up - (canvas_width / 2) * Right;
        view = glm::lookAt(Position, Position + Front, Up);
    }
    void SetFocal(float focal) {
        focal_length = focal;
        optical_center = Position + focal_length * Front;
        float half_height_y = focal_length / tan(glm::radians(fovy));
        float half_width_x = half_height_y * resolutiony / resolutionx;
        pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
        canvas_width = 2 * half_width_x;
        canvas_height = 2 * half_height_y;
    }
    void SetZoom(float fovyinput){
        fovy = fovyinput;
        float half_height_y = focal_length / tan(glm::radians(fovy));
        float half_width_x = half_height_y * resolutiony / resolutionx;
        pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
        canvas_width = 2 * half_width_x;
        canvas_height = 2 * half_height_y;
    }
    void SetResolution(float x, float y) {
        resolutionx = x;
        resolutiony = y;
        float half_height_y = focal_length / tan(glm::radians(fovy));
        float half_width_x = half_height_y * resolutiony / resolutionx;
        pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
        canvas_width = 2 * half_width_x;
        canvas_height = 2 * half_height_y;
    }

private:
    glm::vec3 calRight(glm::vec3 Front) {
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        return glm::normalize(glm::cross(up, Front));
    }
};

#endif

