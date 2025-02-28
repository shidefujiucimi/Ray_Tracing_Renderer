#include <camera.h>
using namespace std;

void Camera::multisample(int i, int j, ofstream& outimage, hittable_list scene) {
    glm::vec3 pixel_color(0, 0, 0);
    for (int sample = 0; sample < samples_per_pixel; sample++) {
        Ray r = get_ray(i, j);
        pixel_color += Shade(r, max_depth, scene);

    }
    write_color(pixel_color/ float(samples_per_pixel), outimage);
    
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