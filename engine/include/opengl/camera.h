#pragma once

#include "shaders/glshaders.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Runa::Opengl
{
    class Camera {
    public:
        Camera(int width, int height, glm::vec3 position);

        // Camera main vectors
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);

        // Prevents the camera from jumping around when first clicking left click
        bool firstClick = true;

        // Window w/h
        int width;
        int height;

        // Camera speed
        float speed = 2.0f;
        float sensitivity = 100.0f;

        // Updates and exports the camera matrix to the Vertex Shader
        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shaders::GLShader &shader, const char *uniform);
        // Handles camera inputs
        void Inputs(SDL_Event event);
        void Tick(float delta);
    };
}