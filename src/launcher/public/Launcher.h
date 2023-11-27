#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <RenderHardwareInterface.h>
#include <Internationalization/Text.h>

class Launcher : public RenderHardwareInterface
{
public:
    explicit Launcher();
    ~Launcher();
    void PreInitialize(ImGuiIO& io) override;
    void Ready() override;
    void EventHandle(SDL_Event event) override;
    void RenderInterface(float delta) override;
    void Render(float delta) override;

private:
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    bool p_open = true;
    void LauncherDoking();

};

#endif // LAUNCHER_H
