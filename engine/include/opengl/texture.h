#pragma once

#include "shaders/glshaders.h"
#include <glad/glad.h>
#include <eastl/string.h>

namespace Runa::Opengl {
    class Texture {
    public:
        Texture(const eastl::string &texdir, const GLenum textype, const GLenum slot, const GLenum format, GLenum pixeltype);
        ~Texture();

        void Bind() const;
        void Unbind() const;
        void SetUniformLocation(const Shaders::GLShader &shader, const char* uniform, const GLuint unit) const;

        GLuint GetTextureID() const {
            return TextureID;
        }
        GLuint GetTextureType() const {
            return TextureType;
        }

    private:
        GLuint TextureID;
	    GLenum TextureType;
    };
}