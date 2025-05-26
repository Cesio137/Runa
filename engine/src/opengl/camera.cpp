#include "opengl/camera.h"
#include <iostream>

namespace Runa::Opengl
{
    Camera::Camera(int width, int height, glm::vec3 position)
    {
        Camera::width = width;
        Camera::height = height;
        Position = position;
    }

    void Camera::Matrix(float FOVdeg, float near_plane, float far_plane, Shaders::GLShader &shader, const char *uniform)
    {
        // Initializes matrices since otherwise they will be the null matrix
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // Makes camera look in the right direction from the right position
        view = glm::lookAt(Position, Position + Orientation, Up);
        // Adds perspective to the scene
        projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, near_plane, far_plane);

        // Exports the camera matrix to the Vertex Shader
        glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
    }

    void Camera::Inputs(SDL_Event event)
    {
        if (event.type = SDL_EVENT_KEY_UP) {
            if (event.key.scancode == SDL_SCANCODE_W) {
                if (event.key.down) { Direction.z = -1.0f; }
                else { Direction.z = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_S) {
                if (event.key.down) { Direction.z = 1.0f; }
                else { Direction.z = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_A) {
                if (event.key.down) { Direction = -glm::normalize(glm::cross(Orientation, Up)); }
                else { Direction.x = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_D) {
                if (event.key.down) { Direction = glm::normalize(glm::cross(Orientation, Up)); }
                else { Direction.x = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_SPACE) {
                if (event.key.down) { Direction.y = 1.0f; }
                else { Direction.y = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_LCTRL) {
                if (event.key.down) { Direction.y = -1.0f; }
                else { Direction.y = 0.0f; }
            }
            if (event.key.scancode == SDL_SCANCODE_LSHIFT) {
                if (event.key.down) { speed = 3.0f; }
                else { speed = 1.0f; }
            }
        }
    }

    void Camera::Tick(float delta) {
        Direction = glm::clamp(Direction, glm::vec3(-1.0f), glm::vec3(1.0f));
        Position += speed * Direction * delta;
    }
}
