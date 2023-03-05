#include "qopengl.h"

#define RENDER_WIDTH  1280
#define RENDER_HEIGHT 720

QOpenGL::QOpenGL(QObject *parent)
    : QObject{parent}
{
    //Set error callback
    glfwSetErrorCallback(error_callback);   

    // Initialize GLFW
    if (!glfwInit())
        return;

    QList<QPair<int, int>> glfwVersion = 
    {
		{4, 6},
        {4, 5},
        {4, 4},
        {4, 3},
        {4, 2},
        {4, 1},
        {4, 0},
        {3, 3},
        {3, 2},
        {3, 1},
        {3, 0},
        {2, 1},
        {2, 0}
    };

    for (int i = 0; i < glfwVersion.size(); i++)
    {
        if (glfwVersion.at(i).first == OPENGL_MAJOR_MIN && glfwVersion.at(i).second < OPENGL_MINOR_MIN)
	    {
            glfwTerminate();
            return;
	    }
        // Set the OpenGL version hint
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwVersion.at(i).first);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwVersion.at(i).second);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // Create a GLFW window
        window = glfwCreateWindow(RENDER_WIDTH, RENDER_HEIGHT, "Lumen", nullptr, nullptr);
        if (window)
        {
            // Make the window's context current
            glfwMakeContextCurrent(window);
            break;
        }
    }

    //Window rezise
    glfwSetWindowSizeCallback(window, window_size_callback);

    //Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, RENDER_WIDTH, RENDER_HEIGHT);

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

    //Render Hardware Interface
    QRHI* RHI = qobject_cast<QRHI*>(parent);
    // Begin Play
    RHI->QBeginPlay();
    // Start a timer count
    deltaTime.start();
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        RHI->QTick(float(deltaTime.elapsed() / 1000));
        deltaTime.restart();

        glfwWaitEvents();
    }

    // Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
    return;
}

void QOpenGL::SetWindowTitle(QString title)
{
    glfwSetWindowTitle(window, title.toUtf8());
}

void QOpenGL::window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap buffers
    glfwSwapBuffers(window);
}

void QOpenGL::error_callback(int error, const char *description)
{
    qDebug() << "Error " << error << ":" << description;
}
