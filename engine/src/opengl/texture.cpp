#include "opengl/texture.h"
#include <stb_image.h>

namespace Runa::Opengl
{
    Texture::Texture(const eastl::string &texdir, const GLenum textype, const GLenum slot, const GLenum format, GLenum pixeltype) {
        // Assigns the type of the texture ot the texture object
        TextureType = textype;

        // Stores the width, height, and the number of color channels of the image
        int texwidth, texheight, numch;
        // Flips the image so it appears right side up
        stbi_set_flip_vertically_on_load(true);
        // Reads the image from a file and stores it in bytes
        unsigned char *bytes = stbi_load(texdir.c_str(), &texwidth, &texheight, &numch, 0);

        // Generates an OpenGL texture object
        glGenTextures(1, &TextureID);
        // Assigns the texture to a Texture Unit
        glActiveTexture(slot);
        glBindTexture(textype, TextureID);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(textype, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(textype, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(textype, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(textype, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
        // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

        // Assigns the image to the OpenGL Texture object
        glTexImage2D(textype, 0, GL_RGBA, texwidth, texheight, 0, format, pixeltype, bytes);
        // Generates MipMaps
        glGenerateMipmap(textype);

        // Deletes the image data as it is already in the OpenGL Texture object
        stbi_image_free(bytes);

        // Unbinds the OpenGL Texture object so that it can't accidentally be modified
        glBindTexture(textype, 0);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &TextureID);
    }

    void Texture::Bind() const {
        glBindTexture(TextureType, TextureID);
    }
    void Texture::Unbind() const {
        glBindTexture(TextureType, 0);
    }

    void Texture::SetUniformLocation(const Shaders::GLShader &shader, const char *uniform, const GLuint unit) const {
        // Gets the location of the uniform
        GLuint texuni = glGetUniformLocation(shader.GetProgramID(), uniform);
        // Shader needs to be activated before changing the value of a uniform
        shader.UseProgram();
        // Sets the value of the uniform
        glUniform1i(texuni, unit);
    }
}
