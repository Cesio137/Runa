#include <array>
#include <iostream>
#include <RenderInterface.h>

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
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File", p_show)) {
            if (ImGui::MenuItem("quit")) rhi.CloseApp();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
        
        ImGui::Begin("Runa", &p_show);
        ImGui::DockSpaceOverViewport(ImGui::GetWindowDockID(), ImGui::GetMainViewport());
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
