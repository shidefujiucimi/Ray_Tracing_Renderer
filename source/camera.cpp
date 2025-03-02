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
void Camera::RenderToimage(hittable_list& scene, const char* _Filename, const Hittable& lights) {
    ofstream outimage;
    outimage.open(_Filename);
    outimage << "P3\n" << resolutionx << ' ' << resolutiony << "\n255\n";

    
    for (int j = 0; j < resolutiony; j++) {
          for (int i = 0; i < resolutionx; i++) {
              glm::vec3 pixel_color(0, 0, 0);
              for (int sample = 0; sample < samples_per_pixel; sample++) {
                  Ray r = get_ray(i, j);
                  pixel_color += Shade(r, max_depth, scene,lights);

              }
              write_color(pixel_color / float(samples_per_pixel), outimage);

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
    double r = color.r;
    double g = color.g;
    double b = color.b;

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    int ir = int(256 * glm::clamp(r, 0.0, 0.999));
    int ig = int(256 * glm::clamp(g, 0.0, 0.999));
    int ib = int(256 * glm::clamp(b, 0.0, 0.999));

    outimage << ir << ' ' << ig << ' ' << ib << '\n';
}
Ray Camera::get_ray(int i, int j) const {
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    glm::vec3 offset = sample_square();

    glm::vec3 pixel_sample = pixel00_loc
        + ((i + offset.x) * Right * pixel_width)
        + ((j + offset.y) * (-Up) * pixel_height);

    glm::vec3 ray_origin = Position;
    glm::vec3 ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}
glm::vec3 Camera::sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return glm::vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

glm::vec3 Camera::Shade(const Ray& ray, int depth,const hittable_list& scene ,const Hittable& lights) {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return glm::vec3(0, 0, 0);

    Hit_record hit_record;
    // If the ray hits nothing, return the background color.
    if (!scene.hit(ray, interval(0.001, infinity), hit_record))
        return background_color;

    scatter_record srec;
    
    glm::vec3 color_from_emission = hit_record.mat->emitted(hit_record.position, hit_record);

    if (!hit_record.mat->scatter(ray, hit_record, srec))
        return color_from_emission;

    if (srec.skip_pdf) {
        return srec.attenuation * Shade(srec.skip_pdf_ray, depth - 1, scene, lights);
    }

    auto light_ptr = make_shared<hittable_pdf>(lights, hit_record.position);
    mixture_pdf p(light_ptr, srec.pdf_ptr);

    Ray scattered = Ray(hit_record.position, p.generate());
    float pdf_value = p.value(scattered.direction);

    float scattering_pdf = hit_record.mat->scattering_pdf(ray, hit_record, scattered);

    glm::vec3 color_from_scatter = (srec.attenuation * scattering_pdf * Shade(scattered, depth - 1, scene, lights)) / pdf_value;

    return color_from_emission + color_from_scatter;

}
