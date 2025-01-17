#include <array>
#include <iostream>
#include "render/render.h"
#include <SDL3/SDL_opengl.h>
#include "glm/vec4.hpp"
#include <lua.h>
#include <luacode.h>
#include <lualib.h>

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

int add_func(lua_State* L) {
    int argc = lua_gettop(L); // Número de argumentos na pilha
    if (argc > 0 && lua_isnumber(L, 1) && lua_isnumber(L, 2)) {
        int x = lua_tointeger(L, 1);
        int y = lua_tointeger(L, 2);
        lua_pushinteger(L, x + y);
        return 1;
    }
    lua_pushinteger(L, 0);
    return 1;
}

int main(int argc, char *argv[]) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    lua_pushcfunction(L, add_func, NULL);
    lua_setglobal(L, "add_func");
    const char* script = R"(
        local result = add_func(10, 12)
        print("Addition:", result)
    )";
    size_t bytecodeSize = 0;
    char* bytecode = luau_compile(script, strlen(script), NULL, &bytecodeSize);
    // Compila o script usando `luau_load`
    if (luau_load(L, "main", bytecode, bytecodeSize, 0)) {
        // Em caso de erro ao compilar, imprime o erro
        std::cerr << "Erro ao compilar script: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        free(bytecode);
        return 1;
    }
    if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
        // Em caso de erro ao executar, imprime o erro
        std::cerr << "Erro ao executar script: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        free(bytecode);
    }

    lua_close(L);
    free(bytecode);
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

