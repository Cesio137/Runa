#ifndef LAUNCHER_H
#define LAUNCHER_H

#ifdef LAUNCHER_H
#define LAUNCHER_FLAGS 1
#endif


#include <RHI/RenderHardwareInterface.h>
#include <QUrl>

class Launcher : public RenderHardwareInterface
{
    Q_OBJECT
public:
    explicit Launcher(QObject *parent = nullptr);
    ~Launcher();
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
    void TriangleController();
    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
    bool vsync = false;
    float fpslimit = 30.0f;

    //Dockspace Launcher
    void LauncherDoking();
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    bool p_open = true;

};

#endif // LAUNCHER_H
