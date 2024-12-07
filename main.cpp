#include <iostream>
#include <RenderInterface.h>

using namespace Runa;

int main(int argc, char *argv[])
{
    RenderInterface rhi(ESDL_Driver::CORE_460);
    int w, h;
    float x, y;
    float scale = 1.0f;
    bool imgui_showdenowindow = true;
    rhi.OnPreInitialize = [&](ImGuiIO &io) {
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    };
    rhi.OnReady = [&]() {
        rhi.SetVSync(1);
    };
    rhi.OnRenderImgui = [&](ImGuiIO &io) {
        bool show = true;
        ImGui::Begin("Runa Interface", &show, ImGuiWindowFlags_NoTitleBar | ImGuiDockNodeFlags_PassthruCentralNode);
        std::string text = "FPS: " + std::to_string(io.Framerate);
        ImGui::Text(text.c_str());
        ImGui::SliderFloat("Triangle scale", &scale, 0.0f, 2.0f);
        ImGui::End();
        ImGui::ShowDemoWindow(&imgui_showdenowindow);
    };
    rhi.OnRender = [&](float delta) {
        SDL_GetWindowSizeInPixels(rhi.GetBackend()->window_ptr, &w, &h);
        x = w/2; y = h/2;
        SDL_Vertex triangle[] = {
            { SDL_FPoint{ x, y - (150 * scale) }, SDL_FColor{ 1, 0, 0, 1}, SDL_FPoint{ 0 } },
            { SDL_FPoint{ x - (200 * scale), y + (150 * scale) }, SDL_FColor{ 0, 0, 1, 1}, SDL_FPoint{ 0 } },
            { SDL_FPoint{ x + (200 * scale), y + (150 * scale) }, SDL_FColor{ 0, 1, 0, 1}, SDL_FPoint{ 0 } },
        };
        SDL_RenderGeometry(rhi.GetBackend()->renderer_ptr, nullptr, triangle, sizeof(triangle) / sizeof(SDL_Vertex), nullptr, 0);

    };
    int code = rhi.Exec();
    if (code) {
        std::cerr << SDL_GetError() << std::endl;
        return code;
    }
    
    return 0;
}
