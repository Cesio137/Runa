#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <RHI/RenderHardwareInterface.h>

class Launcher : public RenderHardwareInterface
{
    Q_OBJECT
public:
    explicit Launcher(QObject *parent = nullptr);
    void PreInitialize(ImGuiIO& io) override;
    void Ready() override;
    void RenderInterface(float delta) override;
    void Render(float delta) override;

private:    
    // Vertex Shader source code
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform float size;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
    "}\0";
    //Fragment Shader source code
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = color;\n"
    "}\n\0";

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    QVector<GLfloat> vertices;
    GLuint VAO, VBO;
    
    // Variables to be changed in the ImGUI window
    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
signals:

};

#endif // LAUNCHER_H
