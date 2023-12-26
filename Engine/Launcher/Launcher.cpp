#include "Launcher.h"

Launcher::Launcher()
{

}

Launcher::~Launcher()
{

}

void Launcher::PreInitialize(ImGuiIO &io)
{
    RenderHardwareInterface::PreInitialize(io);
    winFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    GameUserSettings::SetFrameRateLimit(100);
}

void Launcher::Ready()
{
    RenderHardwareInterface::Ready();
}

void Launcher::EventHandle(SDL_Event event)
{
    RenderHardwareInterface::EventHandle(event);
}

void Launcher::RenderInterface(float delta)
{
    RenderHardwareInterface::RenderInterface(delta);

    ImGuiIO io = ImGui::GetIO();
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", NULL, winFlags);
    ImGui::PopStyleVar(3);

    // Criar um espaço de docking na janela principal
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    // Criar uma janela à esquerda que ocupa metade da largura da tela
    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y));
    ImGui::Begin("Janela Esquerda");
    ImGui::Text("Esta é a janela esquerda");
    ImGui::End();

    // Criar uma janela à direita que ocupa metade da largura da tela
    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y));
    ImGui::Begin("Janela Direita");
    ImGui::Text("Esta é a janela direita");
    ImGui::End();

    // Finalizar a janela principal
    ImGui::End();
}

void Launcher::Render(float delta)
{
    RenderHardwareInterface::Render(delta);
}
