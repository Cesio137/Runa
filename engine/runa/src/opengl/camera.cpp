#include "opengl/camera.h"

namespace runa::opengl {
    camera_c::camera_c(int w, int h, glm::vec3 position) {
        width = w;
        height = h;
        pos = position;
    }

    runa::opengl::camera_c::~camera_c() {

    }

    void camera_c::matrix(float FOVdeg, float near_plane, float far_plane, shader_c &shader, const char *uniform)
    {
        // Initializes matrices since otherwise they will be the null matrix
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // Makes camera look in the right direction from the right position
        view = glm::lookAt(pos, pos + orientation, up);
        // Adds perspective to the scene
        projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, near_plane, far_plane);

        // Exports the camera matrix to the Vertex Shader
        glUniformMatrix4fv(glGetUniformLocation(shader.get_id(), uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
    }

    void camera_c::inputs(SDL_Event event)
    {
        if (event.type = SDL_EVENT_KEY_UP) {
            if (event.key.scancode == SDL_SCANCODE_W) {
                if (event.key.down) { direction.z = -1.0f; }
                else { direction.z = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_S) {
                if (event.key.down) { direction.z = 1.0f; }
                else { direction.z = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_A) {
                if (event.key.down) { direction = -glm::normalize(glm::cross(orientation, up)); }
                else { direction.x = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_D) {
                if (event.key.down) { direction = glm::normalize(glm::cross(orientation, up)); }
                else { direction.x = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_SPACE) {
                if (event.key.down) { direction.y = 1.0f; }
                else { direction.y = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_LCTRL) {
                if (event.key.down) {direction.y = -1.0f; }
                else { direction.y = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_LSHIFT) {
                if (event.key.down) { speed = 3.0f; }
                else { speed = 1.0f; }
            }
        }
    }

    void camera_c::tick(float delta) {
        direction = glm::clamp(direction, glm::vec3(-1.0f), glm::vec3(1.0f));
        pos += speed * direction * delta;
    }
}