#ifndef QUSERSETTINGS
#define QUSERSETTINGS

#include <QObject>
#include <SDL.h>

class RenderingUserSettings : public QObject
{
     Q_OBJECT
public:
    RenderingUserSettings(QObject *parent = nullptr);
    
    //static void SetScreenResolution(int value);
    //static void GetSupportedScreenResolution(int value);
    
    //static void SetFullscreenMode(int value);
    //static Uint32 GetFullscreenMode(int value);

    //static void SetResolutionScaling(int value);
    //static void GetResolutionScaling(int value);

    static void SetVSyncMode(int value);
    static int GetVSyncMode();

    static void SetMaxFPS(Uint8 value);
    static int GetMaxFPS();

private:
     inline static Uint8 max_fps_ = 0;

signals:

};

#endif // QUSERSETTINGS
