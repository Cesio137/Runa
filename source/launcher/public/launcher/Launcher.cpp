#include "Launcher.h"

#include "imgui_internal.h"

Launcher::Launcher(QObject *parent)
{
    Initialize();
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
}

void Launcher::RenderInterface(float delta)
{
    // Criar um espaço de docking na janela principal
    ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    // Usar a função ImGui::DockBuilder*() para dividir o espaço de docking em regiões e atribuir identificadores para elas
    ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(1280.0f, 720.0f));

    ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
    ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
    ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
    ImGuiID dock_up_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.20f, NULL, &dock_main_id);
    ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

    // Usar a função ImGui::DockBuilderDockWindow() para encaixar as janelas nas regiões que você criou
    ImGui::DockBuilderDockWindow("Hello", dock_left_id);
    ImGui::DockBuilderDockWindow("World", dock_right_id);
    ImGui::DockBuilderDockWindow("Foo", dock_up_id);
    ImGui::DockBuilderDockWindow("Bar", dock_down_id);
    ImGui::DockBuilderFinish(dockspace_id);

    // Chamar as funções ImGui::Begin() e ImGui::End() para criar as janelas e widgets dentro delas
    bool show_hello = true;
    bool show_world = true;
    bool show_foo = true;
    bool show_bar = true;

    if (show_hello)
    {
        ImGui::Begin("Hello", &show_hello); // Create a window called "Hello" and append into it.
        ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
        ImGui::End();
    }

    if (show_world)
    {
        ImGui::Begin("World", &show_world);
        /*
        if ()
        {
            ImGui::Text("This is another useful text."); // Display some text (you can use a format strings too)
        // Text that appears in the window
        ImGui::Text("Hello there adventurer!");
        // Checkbox that appears in the window
        ImGui::Checkbox("Draw Triangle?", &drawTriangle);
        // Slider that appears in the window
        ImGui::SliderFloat("Scale", &size, 0.5f, 2.0f);
        // Fancy color editor that appears in the window
        ImGui::ColorEdit4("Albedo", color);
        // Ends the window
        ImGui::Button("engine btn", ImVec2(128.0f, 64.0f));
        
        }
        */
        ImGui::End();
        
    }

    if (show_foo)
    {
        ImGui::Begin("Foo", &show_foo); // Create a window called "Foo" and append into it.
        ImGui::Text("This is some more useful text."); // Display some text (you can use a format strings too)
        ImGui::End();
    }

    if (show_bar)
    {
        // ImGUI window creation
        ImGui::Begin("Bar", &show_bar);
        ImGui::Text("This is even more useful text."); // Display some text (you can use a format strings too)
        ImGui::End();
    }
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
