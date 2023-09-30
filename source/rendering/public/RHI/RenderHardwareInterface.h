#ifndef RHI_H
#define RHI_H

#include <QObject>
#include <opengl/QOpenGL.h>

class RenderHardwareInterface : public QObject
{
Q_OBJECT
public:
    explicit RenderHardwareInterface(QObject *parent = nullptr);
    void Initialize();

    virtual void PreInitialize(ImGuiIO& io);
    virtual void Ready();
    virtual void RenderInterface(float delta);
    virtual void Render(float delta);

    /*ImGui*/
    ImGuiIO* IO = nullptr;

    void CloseApp();
    
private:

    /*Graphics API*/
    QOpenGL *OGL = nullptr;

protected slots:
    void QSlotPreInitialize(ImGuiIO& io);
    void QSlotReady();
    void QSlotRenderInterface(float delta);
    void QSlotRender(float delta);


signals:

};

#endif // RHI_H
