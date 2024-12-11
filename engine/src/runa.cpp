#include <array>
#include <iostream>
#include "render/render.h"

using namespace Runa;

//triangle
int w, h;
float x, y;
float scale = 1.0f;
SDL_Vertex triangle[3];

void UpdateTriangle(SDL_Window* window) {
    SDL_GetWindowSizeInPixels(window, &w, &h);
    x = w / 2;
    y = h / 2;
    triangle[0] = {SDL_FPoint{x, y - (150 * scale)}, SDL_FColor{1, 0, 0, 1}, SDL_FPoint{0}};
    triangle[1] = {SDL_FPoint{x - (200 * scale), y + (150 * scale)}, SDL_FColor{0, 0, 1, 1}, SDL_FPoint{0}};
    triangle[2] = {SDL_FPoint{x + (200 * scale), y + (150 * scale)}, SDL_FColor{0, 1, 0, 1}, SDL_FPoint{0}};
}

int main(int argc, char *argv[]) {
    //imgui
    bool p_show = true;

    RenderInterface rhi(ESDL_Driver::CORE_460);
    rhi.OnPreInitialize = [&](ImGuiIO &io) {
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    };
    rhi.OnReady = [&]() {
        //rhi.SetVSync(1);
        UpdateTriangle(rhi.GetBackend()->window_ptr);
    };
    rhi.OnEventHandle = [&](SDL_Event event) {
        if (event.type == SDL_EVENT_WINDOW_RESIZED) {
            UpdateTriangle(rhi.GetBackend()->window_ptr);
        }
    };
    rhi.OnRenderImgui = [&](ImGuiIO &io) {
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        window_flags |= ImGuiWindowFlags_NoBackground;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        
        ImGui::Begin("Runa", &p_show, window_flags);
        ImGuiID dockspace_id = ImGui::GetID("RunaDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        ImGui::DockSpaceOverViewport(ImGui::GetWindowDockID(), ImGui::GetMainViewport());

        ImGui::BeginMenuBar();
        if (ImGui::BeginMenu("File", p_show)) {
            if (ImGui::MenuItem("quit")) rhi.CloseApp();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();

        if (ImGui::SliderFloat("Scale", &scale, 0.1f, 2.0f)) {
            UpdateTriangle(rhi.GetBackend()->window_ptr);
        }
        ImGui::End();
        //ImGui::ShowDemoWindow(&p_show);
    };
    rhi.OnRender = [&](float delta) {
        SDL_RenderGeometry(rhi.GetBackend()->renderer_ptr, nullptr, triangle, sizeof(triangle) / sizeof(SDL_Vertex),
                           nullptr, 0);
    };
    int code = rhi.Exec();
    if (code) {
        std::cerr << SDL_GetError() << std::endl;
        return code;
    }

    return 0;
}
