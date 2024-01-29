#include "Renderer.h"

void Nanometro::Opengl_EnableAutoSelect(int value)
{
    AUTO_SELECT_OPENGL = value;
}

void Nanometro::Opengl_SetMinorSupportedVersion(int MAJOR, int MINOR)
{
    OPENGL_MAJOR_VERSION = MAJOR;
    OPENGL_MINOR_VERSION = MINOR;
}
