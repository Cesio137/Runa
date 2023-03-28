#include "qopengl.h"

QOpenGL::QOpenGL(QObject *parent)
    : QObject{parent}
{
    connect(this, SIGNAL(BeginPlay()), parent, SLOT(QBeginPlay()));
    connect(this, SIGNAL(Tick(float)), parent, SLOT(QTick(float)));
    connect(this, SIGNAL(ConstructInterface()), parent, SLOT(QConstructInterface()));

    //Set error callback
    glfwSetErrorCallback(error_callback);   

    // Initialize GLFW
    if (!glfwInit())
        return;

    QString ogl_version;

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
        window = glfwCreateWindow(1024, 576, "Lumen", nullptr, nullptr);
        if (window)
        {
            ogl_version = QString::number(glfwVersion.at(i).first) + QString::number(glfwVersion.at(i).second) + "0";
            // Make the window's context current
            glfwMakeContextCurrent(window);
            glfwMaximizeWindow(window);
            break;
        }
    }

    //Window rezise
    glfwSetWindowSizeCallback(window, window_size_callback);

    //Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 1024, 576);

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
    //Remove framerate limit
    glfwSwapInterval(0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version " + ogl_version.toUtf8());

    // Set up docking support
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigDockingWithShift = false;

    // Ative o suporte a ancoragem do ImGui
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    viewport->Flags |= ImGuiViewportFlags_NoDecoration;
    viewport->Flags |= ImGuiViewportFlags_NoTaskBarIcon;
    viewport->Flags |= ImGuiViewportFlags_NoFocusOnAppearing;

    // Begin Play
    emit BeginPlay();
    // Start a timer count
    deltaTime.start();
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        emit Tick(float(deltaTime.elapsed()) / 1000.0f);
        deltaTime.restart();

        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        emit ConstructInterface();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
        glfwWaitEvents();
        FrameRate_Lock();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
    return;
    return;
}

void QOpenGL::SetWindowTitle(QString title)
{
    glfwSetWindowTitle(window, title.toUtf8());
}

GLFWwindow* QOpenGL::GetWindow()
{
	return window;
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

void QOpenGL::FrameRate_Lock()
{
    if( MAX_FRAME_RATE == 0 || float(deltaTime.elapsed()) / 1000.0f >  1.0f/float(MAX_FRAME_RATE) )
    {
        return;
    }
    float sleep = ( 1.0f/float(MAX_FRAME_RATE) * 1000.0f ) - float(deltaTime.elapsed());
    QThread::msleep(sleep);
}
