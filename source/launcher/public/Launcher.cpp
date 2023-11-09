#include "Launcher.h"

Launcher::Launcher()
{
    OpenGL_EnableAutoSelect(false);
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
    RenderUserSettings::SetMaxFPS(30);
}


void Launcher::Ready()
{
    RenderHardwareInterface::Ready();
    dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

}

void Launcher::EventHandle(SDL_Event event)
{
    RenderHardwareInterface::EventHandle(event);
}

void Launcher::RenderInterface(float delta)
{
    RenderHardwareInterface::RenderInterface(delta);
    LauncherDoking();
}

void Launcher::Render(float delta)
{
    RenderHardwareInterface::Render(delta);

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
        ImGui::PushFont(RenderEngineSettings::ContextMenuFont);
        
        if (ImGui::BeginMenu(FText("Launcher").c_str()))
        {
            ImGui::MenuItem(FText("Add project").c_str());

            ImGui::Separator();

            ImGui::MenuItem(FText("Check for updates").c_str());
            if(ImGui::MenuItem(FText("Source code").c_str()))
            {
                SDL_OpenURL("https://github.com/Cesio137/Nanometro");
            }
            if(ImGui::MenuItem(FText("Report issues").c_str()))
            {
                SDL_OpenURL("https://github.com/Cesio137/Nanometro/issues");
            }

            ImGui::Separator();

            if (ImGui::MenuItem(FText("Exit").c_str()))
                CloseApp();
            ImGui::EndMenu();
        }
        ImGui::PopFont();
        ImGui::EndMenuBar();
    }
    ImGui::End();
}
