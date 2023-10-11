#include "Launcher.h"

Launcher::Launcher(QObject *parent)
{
    Init(SDL_INIT_OPENGL);
}

Launcher::~Launcher()
{

}

void Launcher::PreInitialize(ImGuiIO& io)
{
    RenderHardwareInterface::PreInitialize(io);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
}


void Launcher::Ready()
{
    RenderHardwareInterface::Ready();

    dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    
    // Create Vertex Shader Object and get its reference
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    vertices = {
        -0.25f, -0.25f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.25f, -0.25f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner 
    };
    vertices.squeeze();

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Exporting variables to shaders
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
    glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);

    // Criar um espaço de docking na janela principal
    
}

void Launcher::RenderInterface(float delta)
{
    LauncherDoking();
    TriangleController();
}

void Launcher::Render(float delta)
{
	RenderHardwareInterface::Render(delta);

    // Tell OpenGL which Shader Program we want to use
    glUseProgram(shaderProgram);
    // Bind the VAO so OpenGL knows to use it
    glBindVertexArray(VAO);
    // Draw the triangle using the GL_TRIANGLES primitive
    if (drawTriangle)
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);

    // Export variables to shader
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "size"), size);
    glUniform4f(glGetUniformLocation(shaderProgram, "color"), color[0], color[1], color[2], color[3]);
}

void Launcher::TriangleController()
{
    ImGui::Begin("Nanometro");
    ImGui::Text(std::to_string(ImGui::GetIO().DeltaTime).c_str()); // Display some text (you can use a format strings too)
    // Text that appears in the window
    ImGui::Text("Hello there adventurer!");
    // Checkbox that appears in the window
    ImGui::Checkbox("Draw Triangle?", &drawTriangle);
    // Slider that appears in the window
    ImGui::SliderFloat("Scale", &size, 0.5f, 2.0f);
    // Fancy color editor that appears in the window
    ImGui::ColorEdit4("Albedo", color);
    // VSync
    if (ImGui::Checkbox("Enable Vsync", &vsync))
        QUserSettings::SetVSyncMode(vsync);

    if (ImGui::SliderFloat("FPS Target", &fpslimit, 30.0f, 200.0f))
        QUserSettings::SetMaxFPS(fpslimit);
    
    
    ImGui::End();
}

void Launcher::LauncherDoking()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    
    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("Launcher");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Launcher"))
        {
            ImGui::MenuItem("Add project");
            
            ImGui::Separator();
            
            ImGui::MenuItem("Check for updates");
            if(ImGui::MenuItem("Source"))
            {
                SDL_OpenURL("https://github.com/Cesio137/Nanometro");
            }
            if(ImGui::MenuItem("Report issues"))
            {
                SDL_OpenURL("https://github.com/Cesio137/Nanometro/issues");
            }
            
            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
                CloseApp();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }    
    ImGui::End();
}
