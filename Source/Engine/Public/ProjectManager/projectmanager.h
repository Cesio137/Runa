#ifndef QPROJECTMANAGER_H
#define QPROJECTMANAGER_H

#include <QObject>
#include <QDebug>
#include <RHI/RHI.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace std;

class QProjectManager : public QObject
{
Q_OBJECT
public:
    explicit QProjectManager(QObject *parent = nullptr);

public slots:
    void BeginPlay();
    void Tick(float DeltaTime);
    void ConstructInterface();

private:
    QRHI* RHI;
    float fps;
    void SetupDockSpace();

signals:

};

#endif // QPROJECTMANAGER_H
