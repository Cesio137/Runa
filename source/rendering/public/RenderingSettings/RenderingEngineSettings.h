#ifndef RENDERINGENGINESETTINGS_H
#define RENDERINGENGINESETTINGS_H

#define EXAMPLE "${EXAMPLE}"

#include <QObject>
#include <QDebug>
#include <SDL.h>
#include <imgui.h>

using namespace std;

class RenderingEngineSettings : public QObject
{
    Q_OBJECT
public:
    RenderingEngineSettings(QObject *parent = nullptr);
    static int LoadSettings();

    inline static ImFont* ContextMenuFont;
    inline static float ContextMenuFontSize = 14.0f;

    inline static ImFont* DefaultFont;
    inline static float DefaultFontSize = 16.0f;

signals:

};

#endif // RENDERINGENGINESETTINGS_H
