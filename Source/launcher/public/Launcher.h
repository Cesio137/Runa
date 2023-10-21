#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <RenderHardwareInterface.h>
#include <QCoreApplication>
#include <Text/QText.h>
#include <QTranslator>

class Launcher : public RenderHardwareInterface
{
    Q_OBJECT
public:
    explicit Launcher(QObject *parent = nullptr);
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
