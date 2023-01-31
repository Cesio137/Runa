#include "ogl.h"

OGL::OGL(QObject *parent)
    : QObject{parent}
{
    // Initialize GLFW
    glfwInit();
    // EInitialize Opengl
    if (!InitOpenGL())
    {
        glfwTerminate();
        return;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);
    //Auto resize frame buffer
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    glViewport(0, 0, 1024, 768);



    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    BeginPlay();
    timer.start();
    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        Tick(float(timer.elapsed()) / 1000.0f);
        timer.restart();
        //GLFW events
        glfwWaitEvents();
    }
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}

void OGL::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
}

void OGL::BeginPlay()
{
    return;
}

void OGL::Tick(const float DeltaTime)
{
    qDebug() << DeltaTime;
    return;
}

bool OGL::InitOpenGL()
{
    bool isValid = false;
    //Return false if MAJOR is less than 2
    if (MIN_OPENGL_MAJOR_VERSION < 2)
        return false;
    //Check last opengl version supported
    for (int i = 4; i > MIN_OPENGL_MAJOR_VERSION; --i)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, i);
        int max_minor_version;
        switch (i)
        {
        case 2:
            max_minor_version = 1;
        case 3:
            max_minor_version = 3;
        case 4:
            max_minor_version = 6;
        }
        for (int j = max_minor_version; j > (i == MIN_OPENGL_MAJOR_VERSION ? MIN_OPENGL_MINOR_VERSION : 0); --j)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, j);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            window = glfwCreateWindow(1024, 768, "Lumen", NULL, NULL);
            if (window != NULL)
            {
                isValid = true;
                break;
            }
        }
        if (isValid)
            break;
    }

    return isValid;
}
