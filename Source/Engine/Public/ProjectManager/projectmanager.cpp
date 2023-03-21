#include "projectmanager.h"

QProjectManager::QProjectManager(QObject *parent)
        : QObject{parent}
{
    RHI = new QRHI(this, 0);
}

void QProjectManager::BeginPlay()
{
    
}

void QProjectManager::Tick(float DeltaTime)
{
    qDebug() << DeltaTime;
    fps = (1.0f / DeltaTime);
}

void QProjectManager::ConstructInterface()
{
    ImGui::Begin("Lumen");
    SetupDockSpace();
    ImGui::End();
}

void QProjectManager::SetupDockSpace()
{
    int WindowFlag = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    int winWidth;
    int winHeight;
    GLFWwindow* window;
    RHI->getGlfwWindow(window);
    glfwGetWindowSize(window, &winWidth, &winHeight);
    ImGui::SetNextWindowSize( ImVec2( float(winWidth) , float(winHeight) ) );
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    WindowFlag |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("Lumen", new bool(true), WindowFlag);
    ImGui::PopStyleVar(2);
    ImGui::End();
}
