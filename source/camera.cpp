#include <camera.h>
using namespace std;

Camera::Camera(glm::vec3 Positioninput) : Position(Positioninput) {
    optical_center = Position + focal_length * Front;
    view = glm::lookAt(Position, Position + Front, Up);
    float half_height_y = focal_length * tan(glm::radians(fovy));
    float half_width_x = half_height_y / resolutiony * resolutionx;
    pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
    canvas_width = 2 * half_width_x;
    canvas_height = 2 * half_height_y;

    pixel_width = canvas_width/float(resolutionx);
    pixel_height = canvas_height / float(resolutiony);
}
Camera::Camera(glm::vec3 Positioninput, glm::vec3 Rotationinput) : Position(Positioninput), Rotation(Rotationinput) {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(Rotation.x), glm::vec3(1.0, 0.0, 0.0));
    trans = glm::rotate(trans, glm::radians(Rotation.y), glm::vec3(0.0, 1.0, 0.0));
    trans = glm::rotate(trans, glm::radians(Rotation.z), glm::vec3(0.0, 0.0, 1.0));

    Front = trans * glm::vec4(Front, 1.0f);
    Right = trans * glm::vec4(Right, 1.0f);
    Up = trans * glm::vec4(Up, 1.0f);

    optical_center = Position + focal_length * Front;
    view = glm::lookAt(Position, Position + Front, Up);
    float half_height_y = focal_length * tan(glm::radians(fovy));
    float half_width_x = half_height_y / resolutiony * resolutionx;
    pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
    canvas_width = 2 * half_width_x;
    canvas_height = 2 * half_height_y;

    pixel_width = canvas_width / float(resolutionx);
    pixel_height = canvas_height / float(resolutiony);
}

void Camera::SetPosition(glm::vec3 Positioninput) {
    Position = Positioninput;
    optical_center = Position + focal_length * Front;
    pixel00_loc = optical_center + (canvas_height / 2) * Up - (canvas_width / 2) * Right;
    view = glm::lookAt(Position, Position + Front, Up);

}
void Camera::SetRotation(glm::vec3 Rotationinput) {
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
void Camera::SetFocal(float focal) {
    focal_length = focal;
    optical_center = Position + focal_length * Front;
    float half_height_y = focal_length / tan(glm::radians(fovy));
    float half_width_x = half_height_y * resolutiony / resolutionx;
    pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
    canvas_width = 2 * half_width_x;
    canvas_height = 2 * half_height_y;
}
void Camera::SetZoom(float fovyinput) {
    fovy = fovyinput;
    float half_height_y = focal_length / tan(glm::radians(fovy));
    float half_width_x = half_height_y * resolutiony / resolutionx;
    pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
    canvas_width = 2 * half_width_x;
    canvas_height = 2 * half_height_y;
}
void Camera::SetResolution(float x, float y) {
    resolutionx = x;
    resolutiony = y;
    float half_height_y = focal_length / tan(glm::radians(fovy));
    float half_width_x = half_height_y * resolutiony / resolutionx;
    pixel00_loc = optical_center + half_height_y * Up - half_width_x * Right;
    canvas_width = 2 * half_width_x;
    canvas_height = 2 * half_height_y;
}
void Camera::RenderToimage(hittable_list& scene, const char* _Filename) {
    ofstream outimage;
    outimage.open(_Filename);
    outimage << "P3\n" << resolutionx << ' ' << resolutiony << "\n255\n";

    if (AA == false) {
        glm::vec3 pixelposition = pixel00_loc;
        for (int j = 0; j < resolutiony; j++) {
            for (int i = 0; i < resolutionx; i++) {
                glm::vec3 direction = pixelposition - Position;
                glm::vec3 color = Shade(Ray(Position, direction), 0.0, infinity, scene);
                write_color(color, outimage);

                pixelposition += (canvas_width / resolutionx) * Right;
            }
            pixelposition -= canvas_width * Right;
            pixelposition -= (canvas_height / resolutiony) * Up;

        }
    }
    else {
        for (int j = 0; j < resolutiony; j++) {
            for (int i = 0; i < resolutionx; i++) {
                multisample(i, j, outimage, scene);
            }
        }


    }
    outimage.close();
    cout << "finish" << endl;
}

glm::vec3 Camera::calRight(glm::vec3 Front) {
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    return glm::normalize(glm::cross(up, Front));
}
void Camera::write_color(const glm::vec3& color, ofstream& outimage) {

    int ir = int(256 * glm::clamp(double(color.r), 0.0, 1.0));
    int ig = int(256 * glm::clamp(double(color.g), 0.0, 1.0));
    int ib = int(256 * glm::clamp(double(color.b), 0.0, 1.0));

    outimage << ir << ' ' << ig << ' ' << ib << '\n';
}
glm::vec3 Camera::Shade(const Ray& ray, double ray_tmin, double ray_tmax, const hittable_list& scene) {
    glm::vec3 color;
    Hit_record hit_record;
    if (scene.hit(ray, ray_tmin, ray_tmax, hit_record)) {
        color = glm::vec3(
            (hit_record.normal.r + 1.0) * 0.5,
            (hit_record.normal.g + 1.0) * 0.5,
            (hit_record.normal.b + 1.0) * 0.5
        );
    }
    else
        color = glm::vec3(0.0, 0.0, 0.0);


    return color;
}
